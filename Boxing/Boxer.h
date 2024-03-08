#pragma once
#include <iostream>
using namespace std;

#include "Organization.h"
#include "Person.h"
#include "Observer.h"
#include <string>

class Boxer : public Person, public Observer
{
public:
	enum class eCategory{ LOW_WEIGHT, MEDUIN_WEIGHT, HEAVY_WEIGHT };

	Boxer(const string name, int age, const string nickName, double weight, int yearsOfExperience);
	Boxer(const Boxer& boxer);
	Boxer(Boxer&& boxer)noexcept;
	

	void setNickname(const string nickname);
	void setWeight(double weight);
	void setYearsOfExperience(int yearsOfExperience);
	void setinLeague(bool in);
	void setInjured(bool ans);
	 // get in const ** need to update
	const string getNickname()const ;
	double getWeight()const ;
	int getYearsOfExperience()const;
	bool getInMatch()const ;

	void addWin();
	void addLoss();

	int getLosses()const ;
	int getWins() const;

	friend ostream& operator << (ostream& out, const Boxer& boxer);
	// = update const in the begging
	const Boxer& operator = (const Boxer& pre)= delete;
	const Boxer& operator = (Boxer&& pre) = delete;
	bool operator == (const Boxer& other) const;

	const Boxer& operator ++ ();		//prefix
	Boxer operator++ (int);		//postfix

	void notify() const override
	{
		cout << "Boxer: "<<this->getName()<<" Come back to the fight Round starting soon." << endl;

	}

private:
	string nickName;
	double weight;
	int numberOfWins;
	int numberOfLosses;
	int yearsOfExperience;
	bool isInjured=false;
	bool inLeague =false;
};



