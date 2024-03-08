#define _CRT_SECURE_NO_WARNINGS
#include "Boxer.h"

Boxer::Boxer(const string name, int age, const string nickName, double weight, int yearsOfExperience)
	: Person(name, age), weight(weight), numberOfWins(0), numberOfLosses(0), yearsOfExperience(yearsOfExperience) , inLeague(false), isInjured(false)
{
	setNickname(nickName);
	inLeague = false;
}

Boxer::Boxer(const Boxer& boxer)
	: Person(boxer),  weight(boxer.weight), numberOfWins(boxer.numberOfWins), numberOfLosses(boxer.numberOfLosses),
	yearsOfExperience(boxer.yearsOfExperience)
{
	setNickname(boxer.nickName);
}

Boxer::Boxer(Boxer&& boxer) noexcept 
	: Person(std::move(boxer)), nickName(boxer.nickName), weight(boxer.weight), numberOfWins(boxer.numberOfWins),
	numberOfLosses(boxer.numberOfLosses), yearsOfExperience(boxer.yearsOfExperience)
{
}



void Boxer::setNickname(const string nicknameA)
{
	this->nickName = nicknameA;
}

void Boxer::setWeight(double weight)
{
	this->weight = weight;
}

void Boxer::setYearsOfExperience(int yearsOfExperience)
{

	this->yearsOfExperience = yearsOfExperience;
}

const string Boxer::getNickname()const 
{
	return nickName;
}

double Boxer::getWeight()const
{
	return weight;
}

int Boxer::getYearsOfExperience()const
{
	return yearsOfExperience;
}

void Boxer::addWin()
{
	numberOfWins++;
}

void Boxer::addLoss()
{
	numberOfLosses++;
}

int Boxer::getLosses() const
{
	return numberOfLosses;
}

int Boxer::getWins() const
{
	return numberOfWins;
}

void Boxer::setinLeague(bool in)
{
	inLeague = in;
}
void Boxer::setInjured(bool ans)
{
	this->isInjured = ans;
}

bool Boxer::getInMatch()const
{
	return inLeague;
}

ostream& operator<<(ostream& out, const Boxer& boxer)
{
	if (&boxer != nullptr) {


		const Person& person = static_cast<const Person&>(boxer);
		out << person << ", Nickname: " << boxer.nickName << ", Weight: "
			<< boxer.weight << ", Years of Experience: " << boxer.yearsOfExperience << ", Wins: " << boxer.numberOfWins
			<< ", Losses: " << boxer.numberOfLosses;
		return out;
	}
	return out;
}

/*const Boxer& Boxer::operator=(const Boxer& pre)noexcept
{
	if ((this == &pre) || (this == nullptr))
		return *this;

	Person::operator=(pre);
	
		delete[] nickName;

	nickName = new char[strlen(pre.nickName + 1)];
	strcpy(nickName, pre.nickName);

	weight = pre.weight;
	numberOfWins = pre.numberOfWins;
	numberOfLosses = pre.numberOfLosses;
	yearsOfExperience = pre.yearsOfExperience;

	return *this;
}

const Boxer& Boxer::operator=(Boxer&& pre) noexcept
{
	if (this == &pre)
		return *this;

	Person::operator=(std::move(pre));

	delete[] nickName;
	nickName = pre.nickName;
	pre.nickName = nullptr;

	weight = pre.weight;
	numberOfWins = pre.numberOfWins;
	numberOfLosses = pre.numberOfLosses;
	yearsOfExperience = pre.yearsOfExperience;

	return *this;
}
*/

bool Boxer::operator==(const Boxer& other) const
{
	bool secondCheck = dynamic_cast<const Person&>(*this).operator==(dynamic_cast<const Person&>(other));
	if (secondCheck) {
		return (nickName==other.nickName) && (weight == other.weight) &&
			(numberOfWins == other.numberOfWins) && (numberOfLosses == other.numberOfLosses) &&
			(yearsOfExperience == other.yearsOfExperience);
	}
	else
		return false;
}

const Boxer& Boxer::operator++()
{
	++numberOfWins;
	return *this;
}

Boxer Boxer::operator++(int)
{
	Boxer temp = *this;
	++(*this);
	return temp;
}