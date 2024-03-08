#pragma once
#include <iostream>
#include <random>
using namespace std;

#include "Person.h"
#include "Employee.h"
#include "Boxer.h"
#include "Observer.h"

#define DOCTOR_SALARY_CALC 300

class Doctor : public Person, public Employee, public Observer
{
public:
	Doctor(const string name, int age, const string specialty, int yearsExperience , const string company, double salary = 0);

	Doctor(const Doctor& doc);
	Doctor(Doctor&& doc)noexcept;

	void setSpecialty(const string specialty);
	void setExperience(int experience);
	
	const string getSpecialty()const;
	int getExperience()const;

	double getSalary() ;

	
	bool isBoxerInjured(const Boxer* boxer);

	friend ostream& operator << (ostream& out, const Doctor& doc);

	Doctor& operator = (const Doctor& pre);
	const Doctor& operator = (Doctor&& pre)noexcept;
	bool operator == (const Doctor& other) const;

	const Doctor& operator ++ ();		//prefix
	Doctor operator++ (int);		//postfix
	void notify() const override
	{
		cout << " Dr. " << this->getName() << " Please Come Back to the ring! " << endl;
	}
	 Doctor* clone() const;
private:
	string specialty;
	int yearsExperience=0;
	bool inLeague;
};
