#define _CRT_SECURE_NO_WARNINGS
#include "Championship.h"
#include "Championship.h"
#include <cstring>

Championship::Championship(const string name, int prize)
	:  prize(prize)
{
	this->name = name;
}

Championship::Championship(const Championship& champ)
	: currentChampion(champ.currentChampion), prize(champ.prize)
{
	this->name = name;
}

Championship::Championship(Championship&& champ) noexcept
	: currentChampion(champ.currentChampion), name(champ.name), prize(champ.prize) 
{}

void Championship::setCurrentChampion(const Boxer* boxer)
{
	currentChampion = boxer;
}
const Boxer* Championship::getChamption() const
{
    return currentChampion;
}
const string Championship::getName() const
{
	return name;
}

int Championship::getPrize()const
{
	return prize;
}

ostream& operator<<(ostream& out, const Championship& champ)
{
	out << "Championship Details: \n" << endl;
	out << "Championship Name: " << champ.name << endl;
	out << "Prize: " << champ.prize << endl;
	out << "Current Champion: \n\t" << *champ.currentChampion << endl;
	return out;
}

Championship& Championship::operator=(const Championship& pre)
{
	if (this == &pre)
		return *this;

	this->name = pre.name;
	currentChampion = pre.currentChampion;
	prize = pre.prize;
	return *this;
}

const Championship& Championship::operator=(Championship&& pre) noexcept
{
	if (this == &pre)
		return *this;

	name = pre.name;
	

	currentChampion = pre.currentChampion;
	prize = pre.prize;

	return *this;
}

bool Championship::operator==(const Championship& other) const
{
	return (name== other.name) && (prize == other.prize) && (currentChampion == other.currentChampion);
}
