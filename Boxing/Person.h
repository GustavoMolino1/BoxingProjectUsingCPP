#pragma once
#include <iostream>
#include <string>
using namespace std;

class Person
{
public:
	Person(const string name, int age);
	Person(const Person& person);
	Person(Person&& person) noexcept;

	virtual Person* clone()const;

	virtual void EmptyPureVirtual() const = delete;
	void setName(const string name);

	const string getName() const;
	int getAge() const ;

	friend ostream& operator << (ostream& out, const Person& person);

	Person& operator = (const Person& pre);
	const Person& operator = (Person&& pre) noexcept;
	bool operator == (const Person& other) const;

	const Person& operator ++ ();		//prefix
	virtual ~Person() {};

private:
	string name;
	int age;
};