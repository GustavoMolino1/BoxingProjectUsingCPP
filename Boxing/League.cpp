#define _CRT_SECURE_NO_WARNINGS
#include "League.h"
#include "Doctor.h"
#include "Referee.h"
#include "championship.h"
#include "Broadcast.h"
#include "Boxer.h"
#include "BoxingMatch.h"
#include <thread>

#define NUMBER_OF_REGUALR_MATCH 4
#define NUMBER_OF_SEMI_FINAL_MATCH 2
#define NUMBER_OF_FINAL_MATCH 1
#define SPEED_OF_TEXT 5


League::League(const string name, Boxer::eCategory category, Location& location, Broadcast& broadcasts,  Championship& champion)
	: category(category), location(location), broadcast(broadcasts), champion(champion)
{
	setName(name);
}

League::League(League& league)
	: location(league.location), broadcast(league.broadcast), champion(league.champion)
{
category = league.category;
*boxers = *league.boxers;
*referees = *league.referees;
*doctors = *league.doctors;
*judges = *league.judges;

setName(league.name);

	/*for (int i = 0; i < MATCHES_SIZE; i++) {
		if (league.matches[i]) {
			matches[i] = new BoxingMatch(*(league.matches[i]));
		}
		else {
			matches[i] = nullptr;
		}
	}*/
}

League::League(League&& league) noexcept
	: location(league.location), broadcast(league.broadcast), champion(league.champion)
{
	setName(league.name);

	category = league.category;
	*boxers = *league.boxers;
	*referees = *league.referees;
	*doctors = *league.doctors;
	*judges = *league.judges;
	for (int i = 0; i < MATCHES_SIZE; i++)
	{
		matches[i] = league.matches[i];
		league.matches[i] = nullptr;
	}
	*league.boxers = nullptr;
	*league.referees = nullptr;
	*league.doctors = nullptr;
	*league.judges = nullptr;
}

League::~League()
{
	
	for (int i = 0; i < MATCHES_SIZE; i++) {
		delete matches[i];
	}
	for (int i = 0; i < NUMBER_OF_DOCTORS; i++) {
		if (doctors[i] != nullptr) {
			doctors[i]->setInLeague(false);
		}
	}
	// Iterate over the referees array
	for (int i = 0; i < NUMBER_OF_REFEREES; i++) {
		if (referees[i] != nullptr) {
			referees[i]->setInLeague(false);
		}
	}

	// Iterate over the judges array
	for (int i = 0; i < NUMBER_OF_JUDGES; i++) {
		if (judges[i] != nullptr) {
			judges[i]->setInLeague(false);
		}
	}
	for (int i = 0; i < NUMBER_OF_BOXERS; i++) {
		if (boxers[i] != nullptr) {
			boxers[i]->setinLeague(false);
			boxers[i]->setInjured(false);
		}
	}
}

void League::addBoxers( Boxer** boxer)
{ // get an array from Organiztion (max = 8)
	
	for (int i = 0; i < NUMBER_OF_BOXERS; ++i)
		boxers[i] = boxer[i];
}

void League::addReferee( Referee** referee)
{
	for (int i = 0; i < NUMBER_OF_REFEREES; ++i)
		referees[i] = referee[i];
}

void League::printBoxerLeaggue() const
{
	for (int i = 0; i < NUMBER_OF_BOXERS; i++)
	{
		cout << *boxers[i] << endl;
	}
}


void League::addJudge( Judge** judge)
{
	for (int i = 0; i < NUMBER_OF_JUDGES; ++i)
		*judges[i] = *judge[i];
}


void League::addDoctor(Doctor** doctor)
{
	*doctors = *doctor;
}

void League::genarateBracketAndPrint(Boxer** round1Boxers) const
{
	Boxer** semiFinalBoxers2 = new Boxer * [NUMBER_OF_REGUALR_MATCH];
	Boxer**  finalBoxer = new Boxer * [NUMBER_OF_SEMI_FINAL_MATCH];

	srand(static_cast<unsigned int>(time(nullptr)));

	int counterForWinnerArray = 0;
	int randomRefeeree = rand() % NUMBER_OF_REFEREES;

	for (int i = 0; i <= NUMBER_OF_REGUALR_MATCH + 2; i += 2)
	{
		cout << round1Boxers[i]->getName() << ", " << round1Boxers[i + 1]->getName() << endl;
		BoxingMatch* match = new BoxingMatch(round1Boxers[i], round1Boxers[i + 1], referees[randomRefeeree], category, doctors[0]);


		cout << "____________________________Fight! start_________________" << endl;
		match->startMatch();
		cout << "____________________________Fight! end_________________" << endl;
		cout << "THE WINNNER IS " << match->getWinner()->getName() << endl;
		semiFinalBoxers2[counterForWinnerArray++] = match->getWinner();
	}
	cout << "Lets start our next boxer match!" << endl;
	counterForWinnerArray = 0;

	for (int i = 0; i < NUMBER_OF_SEMI_FINAL_MATCH+2; i += 2)
	{
		cout << semiFinalBoxers2[i]->getName() << ", " << semiFinalBoxers2[i + 1]->getName() << endl;
		BoxingMatch* match = new BoxingMatch(semiFinalBoxers2[i], semiFinalBoxers2[i + 1], referees[randomRefeeree], category, doctors[0]);


		cout << "____________________________Fight! start_________________" << endl;
		match->startMatch();
		cout << "____________________________Fight! end_________________" << endl;
		cout << "THE WINNNER IS " << match->getWinner()->getName() << endl;
		finalBoxer[counterForWinnerArray++] = match->getWinner();
	}
	printBracket(round1Boxers, semiFinalBoxers2, finalBoxer);

	
	const string Final1 = finalBoxer[0]->getName();
	const string Final2 = finalBoxer[1]->getName();

	string message;
	message += "Are you ready???? for the FINAL fight?!!?!?!?!? \n  we have a big fight between ";
	message += Final1;
	message += " against ";
	message += Final2;
	message += "  \n Are you ready??? lets Start and see who is going to win the League!!!! \n";
	int delayMilliseconds = SPEED_OF_TEXT;  // Adjust the delay as needed
	for (int i = 0; message[i] != '\0'; ++i) {
		std::cout << message[i] << std::flush;
		std::this_thread::sleep_for(std::chrono::milliseconds(delayMilliseconds));
	}

	
	BoxingMatch* match = new BoxingMatch(finalBoxer[0], finalBoxer[1], referees[randomRefeeree], category, doctors[0]);
	cout << "____________________________Fight! start_________________" << endl;
	match->startMatch();
	cout << "____________________________Fight! end_________________" << endl;
	cout << "THE WINNNER IS " << match->getWinner()->getName() << endl;
	champion.setCurrentChampion(match->getWinner());
	printBracket(round1Boxers, semiFinalBoxers2, finalBoxer);
	

}
void League::printBracket(Boxer** round1Boxers, Boxer** semiFinalBoxers, Boxer** finalBoxer) const
{
	cout << "\n\n" << endl;
	cout << "_" << round1Boxers[0]->getName() << "_                                    _" << round1Boxers[4]->getName() << "_\n";
	cout << "      \\_" << semiFinalBoxers[0]->getName() << "_                     _" << semiFinalBoxers[2]->getName() << "_ / \n";
	cout << "_" << round1Boxers[1]->getName() << "_/       \\                  /       \\_" << round1Boxers[5]->getName() << "_\n";
	cout << "               \\_" << finalBoxer[0]->getName() << "_ VS _" << finalBoxer[1]->getName() << "_/     \n";
	cout << "_" << round1Boxers[2]->getName() << "_        /                 \\        _" << round1Boxers[6]->getName() << "_\n";
	cout << "      \\_" << semiFinalBoxers[1]->getName() << "_/                   \\______/\n";
	cout << "_" << round1Boxers[3]->getName() << "_/                            " << semiFinalBoxers[3]->getName() << " \\_" << round1Boxers[7]->getName() << "_\n";
	
	cout << "\n\n" << endl;
}






Boxer** League::genarateMatchAndReturnWinners(BoxingMatch match) const
{
	Boxer** semiFinalBoxers = new Boxer*[4];
	int counterForSemi = 0;
	cout << "____________________________Fight! start_________________" << endl;
	match.startMatch();
	cout << match.getWinner()->getName() << endl;
	semiFinalBoxers[counterForSemi++] = match.getWinner();
	
	for (int i = 0; i < 4; i++)
	{
		cout << semiFinalBoxers[i]->getName() << endl;

	}
	cout << "____________________________Fight! end_________________" << endl;
	return nullptr;
}

void League::setName(const string name)
{
	this->name = name;
}

const string League::getName() const
{
	return this->name;
}

const string League::getChampionName() const
{
	cout << "champion" << endl;
	return champion.getName();
}

ostream& operator<<(ostream& out, const League& league)
{
	out << "League Details:" << endl;
	out << "Name:" << league.name << endl;
	

	
	/*for (int i = 0; i < NUMBER_OF_BOXERS; ++i) {
		if (league.boxers[i])
			out << "	Boxer " << i + 1 <<" "<< league.boxers[i]->getName() << endl;
	}
	
	out << "Referees: " << endl;
	for (int i = 0; i < NUMBER_OF_REFEREES; ++i) {
		if (league.referees[i])
			out << "	Referee " << i + 1 << " " << league.referees[i]->getName() << endl;
	}

	out << "Doctors: " << endl;
	for (int i = 0; i < NUMBER_OF_DOCTORS; ++i) {
		if (league.doctors[i])
			out << "	Doctor " << i + 1 << " " << league.doctors[i]->getName() << endl;
	}

	out << "Judges: " << endl;
	for (int i = 0; i < NUMBER_OF_JUDGES; ++i) {
		if (league.judges[i])
			out << "	Judge " << i + 1 <<" "<< league.judges[i]->getName() << endl;
	}
	*/
	out << "Location: " << league.location << endl;
	out << "Broadcast: " << league.broadcast << endl;
	out << "Championship: " << league.champion << endl;

	return out;
}

League& League::operator = (const League& other)
{
	if (this == &other)
		return *this;

	// Copy the name
	setName(other.name);

	category = other.category;
	*boxers = *other.boxers;
	*referees = *other.referees;
	*doctors = *other.doctors;
	*judges = *other.judges;

	// Copy the location
	location = other.location;

	// Copy the broadcast
	broadcast = Broadcast(other.broadcast);

	// Copy the championship
	//champion = other.champion;

	return *this;
}

const League& League::operator = (League&& other) noexcept
{
	if (this == &other)
		return *this;
	name = other.name;
	category = other.category;

	for (int i = 0; i < MATCHES_SIZE; ++i)
	{
		delete matches[i];
		matches[i] = other.matches[i];
		other.matches[i] = nullptr;
	}

	for (int i = 0; i < NUMBER_OF_BOXERS; ++i)
	{
		delete boxers[i];
		boxers[i] = other.boxers[i];
		other.boxers[i] = nullptr;
	}

	for (int i = 0; i < NUMBER_OF_REFEREES; ++i)
	{
		delete referees[i];
		referees[i] = other.referees[i];
		other.referees[i] = nullptr;
	}

	for (int i = 0; i < NUMBER_OF_DOCTORS; ++i)
	{
		delete doctors[i];
		doctors[i] = other.doctors[i];
		other.doctors[i] = nullptr;
	}

	for (int i = 0; i < NUMBER_OF_JUDGES; ++i)
	{
		delete judges[i];
		judges[i] = other.judges[i];
		other.judges[i] = nullptr;
	}

	location = move(other.location);
	broadcast = move(other.broadcast);

	return *this;
}
