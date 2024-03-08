#pragma once
#include <iostream>
using namespace std;

#include "Boxer.h"

class Championship
{
public:
	Championship(const string name, int prize);

	Championship(const Championship& champ);
	Championship(Championship&& champ) noexcept;
	void setCurrentChampion(const Boxer* boxer);

	const string getName() const ;
	int getPrize()const;
	const Boxer *getChamption() const;
	

	friend ostream& operator << (ostream& out, const Championship& champ);

	Championship& operator = (const Championship& pre);
	const Championship& operator = (Championship&& pre) noexcept;
	bool operator == (const Championship& other) const;

private:
	const Boxer* currentChampion;
	string name;
	int prize;
};