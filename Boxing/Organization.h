#pragma once
#include "NodeLinked.h"
#include <iostream>
#include <vector>
using namespace std;


class League;
class Judge;
class Referee;
class Boxer;
class Championship;
class Doctor;
class Employee;




class Organization
{
public:
	static Organization* getInstance(const string name);
	static void releaseInstance();
	void setName(const string name);
	const string getName();

	bool addBoxer(const Boxer& boxerToAdd);
	bool addDoctor(const Doctor& DoctorToAdd);
	//bool addreferee(const Referee& RefereeToAdd);
	bool addJudge(const Judge& JudgeToAdd);
	bool addLeague(League& LeagueToAdd);
	bool addEmployee(const Employee& myEmployee);

	// To do
	void getAllDoctors();
	void getAllReferees();
	void getAllJudges();
	
	 vector<Boxer*> getallBoxers()const ;
	Boxer **getBoxerPerLeague() const;
	Doctor **getDoctorsPerLeague() const;
	Judge **getJudgePerLeague() const;
	Referee **getRefereePerLeague() const;

	int getNumOfLeagues() const;
	int getNumOfBoxers() const;
	int getNumOfReferees() const;
	int getNumOfDoctors() const;
	int getNumOfJudges() const;
	int getMaxnumOfLeagues() const {
		return MaxnumOfLeagues;
	}

	int getMaxnumOfBoxers() const {
		return MaxnumOfBoxers;
	}

	int getMaxnumOfReferees() const {
		return MaxnumOfReferees;
	}

	int getMaxnumOfDoctors() const {
		return MaxnumOfDoctors;
	}

	int getMaxnumOfJudges() const {
		return MaxnumOfJudges;
	}

	void PrintAllEmployee() const;
	friend ostream& operator << (ostream& out, const Organization& org);

	Organization& operator = (const Organization& pre);
	const Organization& operator = (Organization&& pre)noexcept;
	bool operator == (const Organization& other) const;

	const Organization& operator += (League& p);
	const Organization& operator += (const Boxer& p);
	const Organization& operator += (const Doctor& p);
	const Organization& operator += (const Judge& p);


private:
	Organization(const string name, int leagues = 5, int boxers = 50, int referees = 20, int doctors = 10, int judges = 20);//those numbers can be empty, too, but they are our default numbers for number of boxer, doctor inc.
	Organization(const Organization& org) = default;
	Organization(Organization&& org) noexcept;
	


protected:
	int numOfLeagues = 0;
	int numOfBoxers = 0;
	int numOfReferees = 0;
	int numOfDoctors = 0;
	int numOfJudges = 0;
	int numofEmployee = 0;
	

	int MaxnumOfLeagues = 0;
	int MaxnumOfBoxers = 0;
	int MaxnumOfReferees = 0;
	int MaxnumOfDoctors = 0;
	int MaxnumOfJudges = 0;
	int MaxOfEmployee = 0;

private:
	static Organization* theOrganization;
	int recordCount;
	static int usersCount;

	string name;
	Employee** allEmployee;
	vector<Boxer*>allBoxers;

	NodeLinked<League*>LeagueNodeList;
	//delete and change in v.4.
	//League** allLeagues;
	//Boxer** allBoxers;
	//Referee** allReferees;

	vector<Referee*>allReferees;
	vector<Judge*>allJudges;
	vector<Doctor*>allDoctors;
	
	//Doctor** allDoctors;
	//Judge** allJudges;
};
