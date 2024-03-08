#define _CRT_SECURE_NO_WARNINGS

#include "Employee.h"

Employee::Employee(const string company, double salary) : salary(salary)
{
	this->company = company;
}

Employee::Employee(const Employee& employee)
{
	this->salary = employee.salary;
	this->inLeague=employee.inLeague;
	this->company = company;
}

Employee::Employee(Employee&& employee) noexcept
{
	this->company = employee.company;
	this->salary = employee.salary;
	this->inLeague=employee.inLeague;

	employee.salary = 0;
}

bool Employee::getInLeague()const
{
	return inLeague;
}
void Employee::setInLeague(bool ans)
{
	inLeague=ans;
}
void Employee::setCompany(const char* company)
{
	this->company = company;
}

const string Employee::getCompany()const
{
	return this->company;
}

void Employee::setSalary(double salary)
{
	this->salary = salary;
}

ostream& operator<<(ostream& out, const Employee& employee)
{
	out << "Company: " << employee.company << ", Salary: " << employee.salary<<" , in League? "<<(employee.inLeague ? "true" : "false");
	return out;
}

Employee& Employee::operator=(const Employee& pre)
{
	if (this == &pre)
		return *this;

	this->company = company;
	this->salary = pre.salary;
	this->inLeague=pre.inLeague;

	return *this;
}

const Employee& Employee::operator=(Employee&& other) noexcept
{
	if (this == &other)
		return *this;

	this->company = other.company;
	this->salary = other.salary;
	this->inLeague=other.inLeague;
	other.salary = 0;
	

	return *this;
}

bool Employee::operator==(const Employee& other) const
{
	return (company== other.company) && (salary == other.salary)&&(inLeague== other.inLeague);
}