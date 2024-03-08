#pragma once
#include <iostream>
using namespace std;

#include "Location.h"
#include "Judge.h"
#include "Boxer.h"

#include <cstdlib>
#include <ctime>

class Referee;
class Doctor;
class Judge;
class Broadcast;
class Boxer;

#define MAX_BOXERS 2
#define MAX_JUDGES 3
#define MAX_SCOREBOARD_LEN 2
#define INJURE_HP 80
#define RECOVER_HP 8

class BoxingMatch
{
public:
	enum class ePunch{
		JAB, CROSS, LEAD_HOOK, REAR_HOOK, LEAD_UPPERCUT, REAR_UPPERCUT, KNOCK_OUT , INJURE 
	};

	
	BoxingMatch(Boxer*firstBoxer,Boxer*secondBoxer,Referee* referee, Boxer::eCategory weightClass, Doctor* doctor);

	BoxingMatch(const BoxingMatch& match);
	BoxingMatch(BoxingMatch&& match) noexcept;
	
	void observerNotifiy() const;

	void setReferee( Referee* referee);
	void setDoctor( Doctor*  doctor);

	void setJudges(Judge** myJudges);
	
	const Referee* getReferee()const ;
	const Doctor* getDoctor()const ;

	void setWeightClass(Boxer::eCategory category);
	Boxer::eCategory getWeightClass()const ;

	 Boxer* getWinner()const ;

	void startMatch() ;

	

	void boxerPunch(const Boxer* boxer, int punch);

	void displayScore()const ;

	bool isMatchFinished()const ;

	
	bool checkBoxerInjured() ;

	friend ostream& operator << (ostream& out, const BoxingMatch& match);

	BoxingMatch& operator = (const BoxingMatch& pre) ;
	const BoxingMatch& operator = (BoxingMatch&& pre) noexcept;
	bool operator == (const BoxingMatch& other) const;
	

private:
	Boxer *boxers[MAX_BOXERS];
	Boxer* winner = nullptr;
	Referee* referee;
	Doctor* doctor;
	Judge *judges[MAX_JUDGES];
	Boxer::eCategory weightClass;
	Observer* observers[MAX_BOXERS+1]; // calling for both boxers, and doctor,referee
	int rounds;
	int currentRound;
	int boxerAScore;
	int boxerBScore;
	bool isFinished;
};
