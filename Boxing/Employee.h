#pragma once
#include "Person.h"

class Employee
{
public:
	Employee(const string company, double salary = 0);

	Employee(const Employee& employee);
	Employee(Employee&& employee)noexcept;

	bool getInLeague() const;
	void setInLeague(bool answer);

	void setCompany(const char* company);
	const string getCompany()const;

	void setSalary(double salary);
	virtual double getSalary() = 0;

	friend ostream& operator << (ostream& out, const Employee& employee);

	Employee& operator = (const Employee& pre);
	const Employee& operator = (Employee&& pre) noexcept;
	bool operator == (const Employee& other) const;

	virtual ~Employee()
	{

	}
private:
	string company;
protected:
	double salary;
	bool inLeague = false;
};

