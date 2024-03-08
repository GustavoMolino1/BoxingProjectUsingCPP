#include "Judge.h"
#include "Boxer.h"

Judge::Judge(const string name, int age, int yearsOfExperience, const string company, double salary) :
	Person(name, age), Employee(company, salary), yearsOfExperience(yearsOfExperience) {}

Judge::Judge(const Judge& other) :Person(other), Employee(other), yearsOfExperience(other.yearsOfExperience) {}

Judge::Judge(Judge&& other) noexcept :Person(other), Employee(other)
{
	this->yearsOfExperience = other.yearsOfExperience;
	other.yearsOfExperience = 0;
}

void Judge::setYearsOfExperience(int yearsOfExperience)
{
	this->yearsOfExperience = yearsOfExperience;
}

int Judge::getYearsOfExperience()const
{
	return this->yearsOfExperience;
}

double Judge::getSalary()
{
	return this->salary * Judge_SALARY_CALC;
}

Boxer* Judge::setWinner(Boxer* boxers[2], int scoreBoxerA, int scoreBoxerB)
{
	if (scoreBoxerA > scoreBoxerB)
	{
		boxers[0]->addWin();
		boxers[1]->addLoss();
		return boxers[0];
		
	}// Return pointer to the first boxer
	else if (scoreBoxerB >= scoreBoxerA)
	{
		boxers[1]->addWin();
		boxers[0]->addLoss();
		return boxers[1];  // Return pointer to the second boxer
	}
	return nullptr;
  // Return nullptr for a draw
}

ostream& operator<<(ostream& out, const Judge& judge)
{
	const Person& person = static_cast<const Person&>(judge);
	const Employee& employee = static_cast<const Employee&>(judge);

	out << person << " " << employee << ", Years of experience: " << judge.yearsOfExperience;
	return out;
}

Judge& Judge::operator = (const Judge& pre)
{
	if (this != &pre)
	{
		Person::operator=(pre);
		Employee::operator=(pre);
	}

	return *this;
}
const Judge& Judge::operator = (Judge&& pre) noexcept
{
	if (this != &pre)
	{
		Person::operator=(pre);
		Employee::operator=(pre);
	}

	return *this;
}

const Judge& Judge::operator ++ ()//prefix
{
	++this->yearsOfExperience;
	return *this;
}
Judge Judge::operator++ (int)//postfix
{
	++this->yearsOfExperience;
	return *this;
}
bool Judge::operator==(const Judge& other) const {
	return (Person::operator==(other) && Employee::operator==(other) && yearsOfExperience == other.yearsOfExperience);

}
