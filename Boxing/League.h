#pragma once

#include "BoxingMatch.h"
#include "Boxer.h"
#include "Championship.h"
#include <thread>

class Doctor;
class Judge;
class Referee;
class Location;
class Broadcast;

#define MATCHES_SIZE 7
#define NUMBER_OF_BOXERS 8
#define NUMBER_OF_REFEREES 4
#define NUMBER_OF_DOCTORS 1
#define NUMBER_OF_JUDGES 3
class League
{
public:
	League(const string name, Boxer::eCategory category, Location& location, Broadcast& broadcasts,  Championship& chamption);
	League(League& league);
	League(League&& league)noexcept;
	virtual ~League();

	void addBoxers( Boxer** boxer);

	void addReferee( Referee** referee);

	void printBoxerLeaggue () const;

	void addJudge( Judge** judge);

	void addDoctor( Doctor** doctor);

	void setName(const string name);
	const string getName() const;

	const string getChampionName() const;

	void genarateBracketAndPrint( Boxer**  round1Boxers) const;
	void printBracket(Boxer** round1Boxers, Boxer** semiFinalBoxers, Boxer** finalBoxer) const;
	Boxer** genarateMatchAndReturnWinners(BoxingMatch match) const;

	friend ostream& operator << (ostream& out, const League& boxer);
	League& operator = (const League& pre);
	const League& operator = (League&& pre) noexcept;

private:
	string name;
	Boxer::eCategory category;
	BoxingMatch* matches[MATCHES_SIZE];
	Boxer* boxers[NUMBER_OF_BOXERS];
	Referee* referees[NUMBER_OF_REFEREES];
	Doctor* doctors[NUMBER_OF_DOCTORS];
	Judge* judges[NUMBER_OF_JUDGES];

	//vector<Judge*>myJudges;
	Location& location;
	Broadcast& broadcast;
	Championship& champion;
};

