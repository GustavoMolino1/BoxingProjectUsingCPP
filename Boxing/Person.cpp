#define _CRT_SECURE_NO_WARNINGS
#include "person.h"


Person::Person(const string str, int age)
{
    this->name = str;
    this->age = age;
}

Person::Person(const Person& person)
{
    this->name = person.name;
    this->age = person.age;
}

Person::Person(Person&& person) noexcept
{
   this->name= person.name;
    this->age = person.age;
    person.age = 0;
}



Person* Person::clone() const
{
    return new Person(*this);
}


void Person::setName(const string name)
{
    this->name = name;
}

const string Person::getName() const
{
      return name;
  
}

int Person::getAge() const
{
    return age;
}

ostream& operator<<(ostream& out, const Person& person)
{   
    if (&person != nullptr) {
        out << "Name: " << person.name << ", Age: " << person.age;
    }
    return out;
}

Person& Person::operator=(const Person& pre)
{
    if (this == nullptr || &pre == nullptr)
    {
        return *this;
    }
    this->name = pre.name;
    this->age = pre.age;

    return *this;
}

const Person& Person::operator=(Person&& other) noexcept
{
    if (this == &other)
    {
        return *this;
    }

    this->name = other.name;
    this->age = other.age;
    other.age = 0;

    return *this;
}

bool Person::operator==(const Person& other) const
{
    return name == other.name && age == other.age;
}

const Person& Person::operator++()
{
    ++age;
    return *this;
}

