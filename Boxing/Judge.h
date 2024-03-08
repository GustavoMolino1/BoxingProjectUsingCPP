#pragma once
#include <iostream>
using namespace std;

#include "Person.h"
#include "Employee.h"


#define Judge_SALARY_CALC 125

class Boxer;

class Judge : public Person, public Employee
{
public:
	Judge(const string name, int age, int yearsOfExperience, const string company, double salary = 0);
	Judge(const Judge& judge);
	Judge(Judge&& judge)noexcept;

	void setYearsOfExperience(int yearsOfExperience);
	int getYearsOfExperience()const ;

	double getSalary() override;

	Boxer* setWinner(Boxer* boxers[2], int scoreBoxerA, int scoreBoxerB);

	friend ostream& operator << (ostream& out, const Judge& judge);

	Judge& operator = (const Judge& pre);
	const Judge& operator = (Judge&& pre)noexcept;

	const Judge& operator ++ ();		//prefix
	Judge operator++ (int);		//postfix
	bool operator == (const Judge& other) const;
	Judge* clone() const override
	{
		return new Judge(*this);
	}



private:
	int yearsOfExperience;
};
