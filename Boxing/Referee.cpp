#define _CRT_SECURE_NO_WARNINGS

#include "Referee.h"

Referee::Referee(const string name, int age, const string speciality, int yearsOfExperience, const string company, double salary)
	:Judge(name, age, yearsOfExperience, company, salary)
{
	this->speciality = speciality;
}

Referee::Referee(const Referee& referee) :Judge(referee)
{
	setSpeciality(referee.speciality);
}

Referee::Referee(Referee&& referee)  noexcept:Judge(referee) 
{
	setSpeciality(referee.speciality);
}


void Referee::setSpeciality(const string speciality)
{
	this->speciality = speciality;
}
const string Referee::getSpeciality() const
{
	return this->speciality;
}

ostream& operator<<(ostream& out, const Referee& referee)
{
	const Judge& person = static_cast<const Judge&>(referee);

	out << person << ", Speciality: " << referee.speciality;
	return out;
}

Referee& Referee::operator = (const Referee& pre)
{
	if (this == &pre)
		return *this;

	Judge::operator=(pre);

	this->speciality = pre.speciality;

	return *this;
}

const Referee& Referee::operator = (Referee&& pre) noexcept
{
	if (this == &pre)
		return *this;

	Judge::operator=(std::move(pre));
	speciality = pre.speciality;
	return *this;
}

bool Referee::operator == (const Referee& other) const
{
	return (this->speciality== other.speciality);
}