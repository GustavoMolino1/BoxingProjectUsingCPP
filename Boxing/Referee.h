#pragma once
#include <iostream>
using namespace std;
#include "Observer.h"
#include "Judge.h"

#define Referee_SALARY_CALC 130

class Referee : public Judge,public Observer
{
public:
	Referee(const string name, int age, const string speciality, int yearsOfExperience, const string company, double salary = 0);

	Referee(const Referee& referee);
	Referee(Referee&& referee) noexcept;

	void setSpeciality(const string speciality);
	const string getSpeciality() const;

	friend ostream& operator << (ostream& out, const Referee& referee);
	Referee& operator = (const Referee& pre);
	const Referee& operator = (Referee&& pre) noexcept;

	bool operator == (const Referee& other) const;
	Referee* clone() const override
	{
		return new Referee(*this);
	}

	void notify() const override
	{
		cout << " I'm Referee: "<<this->getName()<<" calling to the Boxers dcotor to Come back to the fight" << endl;
	}

private:
	string speciality;
};

