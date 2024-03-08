#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <chrono>
#include "BoxingMatch.h"
#include "Doctor.h"
#include "Referee.h"

#include <thread>
#include <cstdlib>
#include <ctime>

#define SPEED_OF_TEXT 10

const char* punchNames[] = { "JAB","CROSS","LEAD_HOOK","REAR_HOOK","LEAD_UPPERCUT","REAR_UPPERCUT","KNOCK_OUT","INJURE" };
const int punchValues[] = { 8, 15, 14, 15,8, 10,  100, -100 };



BoxingMatch::BoxingMatch(Boxer* firstBoxer, Boxer* secondBoxer, Referee* referee, Boxer::eCategory weightClass, Doctor* doctor):
	referee(referee),
	doctor(doctor),
	weightClass(weightClass),
	rounds(12),
	currentRound(1),
	boxerAScore(100),
	boxerBScore(100),
	isFinished(false)
	
{
	for (int i = 0; i < MAX_JUDGES; ++i) {
		judges[i] = nullptr;  // Initialize each element to nullptr
	}
	boxers[0] = firstBoxer;
	boxers[1] = secondBoxer;
	
	observers[0] = firstBoxer;
	observers[1] = secondBoxer;
	observers[2] = doctor;
	
	
	
}

BoxingMatch::BoxingMatch(const BoxingMatch& match) :
	referee(match.referee),
	doctor(match.doctor),
	rounds(match.rounds),
	weightClass(match.weightClass),
	currentRound(match.currentRound),
	boxerAScore(match.boxerAScore),
	boxerBScore(match.boxerBScore),
	isFinished(match.isFinished),
	observers()
	
{
	for (int i = 0; i < MAX_BOXERS; ++i)
		boxers[i] = match.boxers[i];

	for (int i = 0; i < MAX_JUDGES; ++i)
		judges[i] = match.judges[i];

	winner = match.winner;
}

BoxingMatch::BoxingMatch(BoxingMatch&& match) noexcept :
	referee(match.referee),
	doctor(match.doctor),
	rounds(match.rounds),
	weightClass(match.weightClass),
	currentRound(match.currentRound),
	boxerAScore(match.boxerAScore),
	boxerBScore(match.boxerBScore),
	isFinished(match.isFinished),
	observers()
{
	for (int i = 0; i < MAX_BOXERS; ++i)
		boxers[i] = move(match.boxers[i]);
	for (int i = 0; i < MAX_JUDGES; ++i)
		judges[i] = nullptr;

	winner = match.winner;
	match.winner = nullptr;
}

void BoxingMatch::setJudges(Judge** myJudges)
{
	for (int i = 0; i < MAX_JUDGES; ++i) {
		judges[i] = myJudges[i];  // Copy the Judge* pointers
	}
}





void BoxingMatch::observerNotifiy() const
{
	cout << "---------------------------------------------------" << endl;
	
	referee->notify();
	for (int i = 0; i < MAX_BOXERS+1; ++i)
	{
		if (observers[i] != nullptr)
		{
			observers[i]->notify();
		}
	}
	std::this_thread::sleep_for(std::chrono::seconds(5));
	cout << "Lets Fight!" << endl;
	cout << "---------------------------------------------------" << endl;

}

void BoxingMatch::setReferee( Referee* referee)
{
	referee = referee;
}

void BoxingMatch::setDoctor( Doctor*  doctor)
{
	doctor = doctor;
}

const Referee* BoxingMatch::getReferee()const 
{
	return referee;
}

const Doctor* BoxingMatch::getDoctor()const
{
	if(this!=nullptr)
		return doctor;
	return NULL;
}

void BoxingMatch::setWeightClass(Boxer::eCategory category)
{
	weightClass = category;
}

Boxer::eCategory BoxingMatch::getWeightClass()const 
{
	return weightClass;
}

 Boxer* BoxingMatch::getWinner()const 
{
	return winner;
}

void BoxingMatch::startMatch()  
{
	srand(static_cast<unsigned int>(time(nullptr)));
	int numberOfTotalPunchsForRound = rand() % 7 + 1, whichBoxerPunch = rand() % 2; // for the first Round!. 
	const string boxer1Name = boxers[0]->getName();
	const string boxer2Name = boxers[1]->getName();

	string message;
	message+= "Welcome to the fight!! Today we have a big fight between ";
	message += boxer1Name;
	message+= " against " ;
	message += boxer2Name;
	message += " Are you ready??? lets Start! \n";
	int delayMilliseconds = SPEED_OF_TEXT;  // Adjust the delay as needed
	for (int i = 0; message[i] != '\0'; ++i) {
		std::cout << message[i] << std::flush;
		std::this_thread::sleep_for(std::chrono::milliseconds(delayMilliseconds));
	}
	for (int i = 0; i < rounds && !isFinished && winner == nullptr; i++)
	{
		if(i!=0)observerNotifiy();
		cout << "Round: " << currentRound << endl;


		for (int i = 0; i < numberOfTotalPunchsForRound; i++)
		{
			srand(static_cast<unsigned int>(time(nullptr)));  // Seed the random number generator

			int randomIndex = rand() % 6;  // Generate a random index from 0 to 5

			
			if (boxers[whichBoxerPunch]->getName() == boxer1Name)
			{
				boxerBScore -= punchValues[randomIndex];
			}
			else
			{
				boxerAScore -= punchValues[randomIndex];
			}

			boxerPunch(boxers[whichBoxerPunch], randomIndex);
			whichBoxerPunch = rand() % 2;
			if (checkBoxerInjured())break;; // checking the 'status of the boxer match (the HP of per Boxer.)

		}
		cout << " \n ~~~~~~~~~~~~~~~~~~~~~~~~ END ROUND ~~~~~~~~~~~~~~~~~~~~~~~~\n " << endl;
		displayScore();
		currentRound++;
		numberOfTotalPunchsForRound = rand() % 7 + 1;
		whichBoxerPunch = rand() % 2;
	}
	if (winner != nullptr)
	{
		cout << "Ladies and gentlemen! The winner of our battle is..." << winner->getName() << "\n\n"<<endl;
		winner->addWin();
		winner->getName() == boxer1Name ? boxers[1]->addLoss() : boxers[0]->addLoss();
	}
	else
	{
	
		
		cout << "The fight ended without a decision! Now the judges are discussing who will be the winner!"<<endl;
		
			winner=judges[0]->setWinner(boxers, boxerAScore, boxerBScore); // the judge in the number 0, if the senior judge
			if (winner != nullptr) {
				cout << "As the senior judge of the fight that took place, I rule that " << winner->getName() << " won!" << "\n\n" << endl;
				
			}
		else {
				
			winner = judges[0]->setWinner(boxers, boxerAScore, boxerBScore); // the judge in the number 0, if the senior judge
			cout << "As the senior judge of the fight that took place, I rule that " << winner->getName() << " won!" << "\n\n" << endl;
		}
		// צריך להוסיף לשלב הבא. 
		// לשחרר את המפסיד. 
		this->isFinished = true;
		
	}

		
	
}



void BoxingMatch::boxerPunch(const Boxer* boxer, int punchIndex)
{
	string message;
	message += "\n";
	message += "WOW!! did you see that punch? ";
	message += boxer->getName();
	message += " gave him ";
	message += punchNames[punchIndex];

	
	int delayMilliseconds = SPEED_OF_TEXT;  // Adjust the delay as needed
	for (int i = 0; message[i] != '\0'; ++i) {
		std::cout << message[i] << std::flush;
		std::this_thread::sleep_for(std::chrono::milliseconds(delayMilliseconds));
	}


}

void BoxingMatch::displayScore()const
{
	cout << "Current HP A:" << boxerAScore << ", B:" << boxerBScore << endl;
}
bool BoxingMatch::isMatchFinished()const
{
	return isFinished;
}
BoxingMatch& BoxingMatch::operator=(const BoxingMatch& pre)
{
	if (this == &pre)
		return *this;
	referee = pre.referee;
	doctor = pre.doctor;
	weightClass = pre.weightClass;
	rounds = pre.rounds;
	currentRound = pre.currentRound;
	boxerAScore = pre.boxerAScore;
	boxerBScore = pre.boxerBScore;
	isFinished = pre.isFinished;

	for (int i = 0; i < MAX_BOXERS; ++i)
		boxers[i] = pre.boxers[i];


	winner = pre.winner;

	return *this;
}
const BoxingMatch& BoxingMatch::operator=(BoxingMatch&& pre) noexcept
{
	if (this == &pre)
		return *this;


	referee = pre.referee;
	doctor = pre.doctor;
	weightClass = pre.weightClass;
	rounds = pre.rounds;
	currentRound = pre.currentRound;
	boxerAScore = pre.boxerAScore;
	boxerBScore = pre.boxerBScore;
	isFinished = pre.isFinished;

	for (int i = 0; i < MAX_BOXERS; ++i)
		boxers[i] = std::move(pre.boxers[i]);
	for (int i = 0; i < MAX_BOXERS + 1; i++)
		observers[i] = pre.observers[i];


	winner = pre.winner;
	pre.winner = nullptr;

	return *this;
}
bool BoxingMatch::operator==(const BoxingMatch& other) const
{
	// Compare all the member variables for equality
	if (rounds != other.rounds ||
		currentRound != other.currentRound ||
		boxerAScore != other.boxerAScore ||
		boxerBScore != other.boxerBScore ||
		isFinished != other.isFinished ||
		weightClass != other.weightClass ||
		winner != other.winner ||
		referee != other.referee ||
		doctor != other.doctor)
	{
		return false;
	}

	// Compare the boxers
	for (int i = 0; i < MAX_BOXERS; ++i)
	{
		if (!( * boxers[i] == *other.boxers[i]))
		{
			return false;
		}
	}
	for (int i = 0; i < MAX_JUDGES; ++i)
	{
		cout << *judges[i] << endl;
	}

	// Compare the judges
	for (int i = 0; i < MAX_JUDGES; ++i)
	{
		if (!(*judges[i] == *other.judges[i]))
		{
			return false;
		}
	}
	for (int i = 0; i < MAX_BOXERS + 1; i++)
		if (observers[i] != other.observers[i])
			return false;

	// All member variables are equal
	return true;
}
ostream& operator << (ostream& out, const BoxingMatch& match)
{
	out << "Boxing Match:";
	out << "Boxers:" << endl;
	for (int i = 0; i < MAX_BOXERS; ++i) {
		if (match.boxers[i])
			out << "Boxer " << i + 1 << ": " << match.boxers[i]->getName() << endl;
	}

	BoxingMatch regulatMAtch(match);
	out << "Winner: " << (match.winner ? match.winner->getName() : "None") << endl;

	out << "Weight Class: ";
	switch (match.weightClass) {
	case Boxer::eCategory::LOW_WEIGHT:
		cout << "Low Weight" << endl;
		break;
	case Boxer::eCategory::MEDUIN_WEIGHT:
		cout << "Medium Weight" << endl;
		break;
	case Boxer::eCategory::HEAVY_WEIGHT:
		cout << "Heavy Weight" << endl;
		break;
	default:
		cout << "Unknown" << endl;
	}

	out << "Rounds: " << match.rounds << endl;
	out << "Current Round: " << match.currentRound << endl;
	out << "Boxer A Score: " << match.boxerAScore << endl;
	out << "Boxer B Score: " << match.boxerBScore << endl;
	out << "Finished: " << (match.isFinished ? "Yes" : "No") << endl;
	out << "doctor of the match: " << *match.doctor << endl;
	out << "Referee of the match: " << match.referee << endl;

	return out;

}
void typeWriterEffect(const char* message, int delayMilliseconds) {
	size_t length = strlen(message);
	for (size_t i = 0; i < length; ++i) {
		std::cout << message[i] << std::flush;  // Print the character without buffering
		std::this_thread::sleep_for(std::chrono::milliseconds(delayMilliseconds));
	}
}





bool BoxingMatch::checkBoxerInjured() 
{
	if (boxers[0] != nullptr && boxers[1] != nullptr)
	{

		if (boxerAScore <= INJURE_HP) {
			cout << " \n Wait! Did you see what happened?" << boxers[0]->getName() << " is injured! \n Our doctor is checking his condition maybe he won't be able to continue the fight!" << endl;
			if (boxerAScore <= 40)
			{
				isFinished = true;
				winner = boxers[1];
				return true;
			}
			
			if (!doctor->isBoxerInjured(boxers[0]))
				{
					  isFinished = true;
						winner = boxers[1];
						return true;
				}
				else
					boxerAScore += RECOVER_HP;

		}
		if (boxerBScore <= INJURE_HP) {
			cout << " \n Wait! Did you see what happened?" << boxers[1]->getName() << " is injured! \n Our doctor is checking his condition maybe he won't be able to continue the fight!" << endl;
		
			if (boxerBScore <= 40)
			{
				isFinished = true;
				winner = boxers[0];
				return true;
			}
			if (!doctor->isBoxerInjured(boxers[1]))
			{
				
				isFinished = true;
				winner = boxers[0];
				return true;
			}
			else
				boxerBScore += RECOVER_HP;
		}
	}
	return false;

}