#define _CRT_SECURE_NO_WARNINGS

#include "Doctor.h"

Doctor::Doctor(const string name, int age, const string specialty, int yearsExperience, const string company, double salary) :
	Person(name, age), Employee(company, salary), yearsExperience(yearsExperience)
{
	setSpecialty(specialty);
}

Doctor::Doctor(const Doctor& doc) :Person(doc), Employee(doc)
{
	setSpecialty(doc.specialty);
	setExperience(doc.yearsExperience);
}

Doctor::Doctor(Doctor&& doc) noexcept :Person(doc), Employee(doc)
{
	this->specialty=doc.specialty;

	this->yearsExperience = doc.yearsExperience;
	this->inLeague = doc.inLeague;
	doc.yearsExperience = 0;
}



void Doctor::setSpecialty(const string specialty)
{
	this->specialty = specialty;
	
}

void Doctor::setExperience(int experience)
{
	this->yearsExperience = experience;
}

const string Doctor::getSpecialty()const
{
	return this->specialty;
}

int Doctor::getExperience()const
{
	return this->yearsExperience;
}

double Doctor::getSalary() 
{
	return this->salary * DOCTOR_SALARY_CALC;
}

bool Doctor::isBoxerInjured(const Boxer* boxer)
{
	srand(static_cast<unsigned int>(time(nullptr)));
	bool answer; // 
	int randomNumber = rand() % 10;  // Generate a random number between 0 and 9
	if (randomNumber <= 5) {
		answer = true;
	}
	else {
		answer = false;
	}

	if (answer) // boxer can continue
		cout << "" << boxer->getName() << " is currently recovering, but he will continue the fight!" << endl;
	else
		cout << "Wow.. " << boxer->getName() << " got hit a lot.. he can't continue the fight"<<endl;

	
	return answer;
}

ostream& operator<<(ostream& out, const Doctor& doc)
{
	const Person& person = static_cast<const Person&>(doc);
	const Employee& employee = static_cast<const Employee&>(doc);

	out << person << " " << employee << ", Specialty: " << doc.specialty << ", Years of experience: " << doc.yearsExperience;
	return out;
}

Doctor& Doctor::operator = (const Doctor& other)
{
	if (this != &other)
	{
		Person::operator=(other);
		Employee::operator=(other);
		specialty=other.specialty;

		yearsExperience = other.yearsExperience;
	}

	return *this;
}
const Doctor& Doctor::operator = (Doctor&& other) noexcept
{
	if (this != &other)
	{
		Person::operator=(other);
		Employee::operator=(other);
		specialty = other.specialty;
		yearsExperience = other.yearsExperience;
	}
	return *this;
}
bool Doctor::operator == (const Doctor& other) const
{
	return Person::operator==(other) && Employee::operator==(other) && yearsExperience == other.yearsExperience && (this->specialty== other.specialty);
}

const Doctor& Doctor::operator ++ ()//prefix
{
	++this->yearsExperience;
	return *this;
}
Doctor Doctor::operator++ (int)//postfix
{
	++this->yearsExperience;
	return *this;
}

Doctor* Doctor::clone() const
{
	return new Doctor(*this);
}
