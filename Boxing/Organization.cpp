#define _CRT_SECURE_NO_WARNINGS

#include "Organization.h"
#include "Boxer.h"
#include "Doctor.h"
#include "Person.h"
#include "League.h"
#include "Referee.h"
#include "League.h"

vector<Boxer*> myBoxers;

Organization* Organization::theOrganization = nullptr;
int Organization::usersCount = 0;

Organization::Organization(const string name, int leagues, int boxers, int referees, int doctors, int judges) :MaxnumOfBoxers(boxers), MaxnumOfDoctors(doctors), MaxnumOfJudges(judges), MaxnumOfLeagues(leagues), MaxnumOfReferees(referees), recordCount(0), allBoxers(), allReferees(), allJudges(), allDoctors()
{

	allEmployee = new Employee * [100];
	setName(name);
	
	
}
int Organization::getNumOfLeagues() const
{
	return numOfLeagues;
}

int Organization::getNumOfBoxers() const
{
	return numOfBoxers;
}

int Organization::getNumOfReferees() const
{
	return numOfReferees;
}

int Organization::getNumOfDoctors() const
{
	return numOfDoctors;
}

int Organization::getNumOfJudges() const
{
	return numOfJudges;
}
//Boxer**
 vector<Boxer*>Organization::getallBoxers() const
{
	return allBoxers;
}
bool Organization::addBoxer(const Boxer& bo)
{
	if (numOfBoxers == MaxnumOfBoxers) 
	{
		cout << "Full! Maximun Boxers" << endl;
		return false;
	}
//	allBoxers[numOfBoxers++] = new Boxer(bo);
	allBoxers.push_back(new Boxer(bo));
	numOfBoxers++;

	cout << "Welcome " << bo.getName() << " To our organization Get ready for the start of the league" << endl;
	return true;
}
Boxer** Organization::getBoxerPerLeague() const 
{
	Boxer** arrayOfBoxers = new Boxer* [NUMBER_OF_BOXERS];

	int counterOfBoxers = 0;
	for (int i = 0; i < numOfBoxers && counterOfBoxers != NUMBER_OF_BOXERS; i++)
	{
		if (!this->allBoxers[i]->getInMatch())
		{
			arrayOfBoxers[counterOfBoxers++] = allBoxers[i];
			this->allBoxers[i]->setinLeague(true);
		}
	}
	return arrayOfBoxers;
}
Doctor** Organization::getDoctorsPerLeague() const 
{
	
	Doctor** arrayOfDoctors = new Doctor*[NUMBER_OF_DOCTORS];
	int counterOfDoctors = 0;
	for (int i = 0; i < numOfDoctors && counterOfDoctors != NUMBER_OF_DOCTORS; i++)
	{

		if (!this->allDoctors[i]->getInLeague())
		{
			arrayOfDoctors[counterOfDoctors++] = allDoctors[i];
			this->allDoctors[i]->setInLeague(true);
		}
	}
	return arrayOfDoctors;
}
Judge** Organization::getJudgePerLeague() const
{
	Judge** arrayOfJudge = new Judge *[NUMBER_OF_JUDGES];
	int counterOfJudge = 0;
	for (int i = 0; i < numOfJudges && counterOfJudge != NUMBER_OF_JUDGES; i++)
	{

		if (!this->allJudges[i]->getInLeague())
		{
			arrayOfJudge[counterOfJudge++] = allJudges[i];
			this->allJudges[i]->setInLeague(true);
		}
	}
	return arrayOfJudge;
}
Referee** Organization::getRefereePerLeague() const
{
	Referee** arrayOfReferee = new Referee*[NUMBER_OF_REFEREES];
	int counterOfReferee = 0;
	for (int i = 0; i < numOfReferees && counterOfReferee != NUMBER_OF_REFEREES; i++)
	{
		if (!this->allReferees[i]->getInLeague())
		{
			cout << "Welcome Referee " << this->allReferees[i]->getName() << endl;
			arrayOfReferee[counterOfReferee++] = allReferees[i];
			this->allReferees[i]->setInLeague(true);
		}
	}
	return arrayOfReferee;
}

bool Organization::addDoctor(const Doctor& doc)
{
	if (numOfDoctors == MaxnumOfDoctors)
		return false;
	//allDoctors[numOfDoctors++] = new Doctor(doc);
	
	allEmployee[0] =new Doctor(doc);
	cout << "Welcome Dr." << doc.getName() << endl;
	return true;
}

bool Organization::addJudge(const Judge& jud)
{
	if (numOfJudges == MaxnumOfJudges)
		return false;
	allJudges[numOfJudges++] = new Judge(jud);
	//= type.clone();
	cout << jud.getName() << " Welcome Judge!" << endl;
	return true;
}

bool Organization::addLeague(League& leg)
{
	if (numOfLeagues == MaxnumOfLeagues)
		return false;
	//allLeagues[numOfLeagues++] = new League(leg);
	LeagueNodeList.add(new League(leg));
	
	cout << "New League added " << endl;
	LeagueNodeList.print();
	return true;
}

bool Organization::addEmployee(const Employee& myEmployee)
{
	if (const Doctor* doctor = dynamic_cast<const Doctor*>(&myEmployee))
	{
		if (numOfDoctors == MaxnumOfDoctors)
			return false;
	
		Doctor* d = doctor->clone();
		allEmployee[numofEmployee++] = new Doctor(*d);
		numOfDoctors++;
		getAllDoctors();
		return true;
	}
	else if (const Referee* referee = dynamic_cast<const Referee*>(&myEmployee))
	{
		if (numOfReferees == MaxnumOfReferees)
			return false;
		// Clone the Referee object and add it to the organization
		Referee* clonedReferee = referee->clone();
		allEmployee[numofEmployee++] = new Referee(*clonedReferee);
		numOfReferees++;
		getAllReferees();
		return true;
	}
	else if (const Judge* judge = dynamic_cast<const Judge*>(&myEmployee))
	{
		if (numOfJudges == MaxnumOfJudges)
			return false;
		Judge* clonedJudge = judge->clone();
		allEmployee[numofEmployee++] =new Judge(*clonedJudge);
		numOfJudges++;
		getAllJudges();
		return true;
	}

	return false;
}

void Organization::getAllDoctors()
{
	for (size_t i = 0; i < numofEmployee; i++)
	{
		if (Doctor* doctor = dynamic_cast<Doctor*>(allEmployee[i])) {
			if(doctor)
				allDoctors.push_back(doctor);
		}
	}
}

void Organization::getAllReferees()
{
	Referee** refereesArray = new Referee * [numOfReferees];
	for (size_t i = 0; i < numofEmployee; i++)
	{
		if ( Referee* Refere = dynamic_cast< Referee*>(allEmployee[i])) {
			if (Refere)
				allReferees.push_back(Refere);
		}
	}
}

void Organization::getAllJudges()
{
	Judge** judgeesArray = new Judge * [numOfJudges];
	for (size_t i = 0; i < numofEmployee; i++)
	{
		if ( Judge* judge = dynamic_cast< Judge*>(allEmployee[i])) {
			if (judge)
			{
				allJudges.push_back(judge);
			}
		}
	}
}



Organization* Organization::getInstance(const string name)
{
	if (theOrganization == nullptr)
		theOrganization = new Organization(name);
	usersCount++;
	return theOrganization;
}

void Organization::releaseInstance()
{
	usersCount--;
	if (usersCount == 0) {
		delete theOrganization;
		theOrganization = nullptr;
	}

}

void Organization::setName(const string name)
{
	this->name = name;
}

const string Organization::getName()
{
	return name;
}


ostream& operator<<(ostream& out, const Organization& org)
{
//	return out << "Name: " << org.name;
	out << "Organiztion Details:" << endl;
	out << "Name:" << org.name << endl;

	
	for (int i = 0; i < org.getNumOfBoxers(); ++i) {
		if (org.allBoxers[i]) 
			out << "	Boxer  " << i + 1 << " " << org.allBoxers[i]->getName() << endl;
	}
	
	for (int i = 0; i < org.getNumOfBoxers(); ++i) {
		if (org.allBoxers[i])
			out << "	Boxer  " << i + 1 << " " << org.allBoxers[i]->getName() << endl;
	}


	out << "Referees: " << endl;
	for (int i = 0; i < org.getNumOfReferees(); ++i) {
		if (org.allReferees[i])
			out << "	Referee  " << i + 1 << " " << org.allReferees[i]->getName() << endl;
	}

	out << "Doctors: " << endl;
	for (int i = 0; i < org.getNumOfDoctors(); ++i) {
		if (org.allDoctors[i])
			out << "	Doctor  " << i + 1 << " " << org.allDoctors[i]->getName() << endl;
	}

	out << "Judges: " << endl;
	for (int i = 0; i < org.getNumOfJudges(); ++i) {
		if (org.allJudges[i])
			out << "	Judge  " << i + 1 << " " << org.allJudges[i]->getName() << endl;
	}
	return out;
	
}

void Organization::PrintAllEmployee() const
{
	for (size_t i = 0; i < numofEmployee; i++)
	{
		if (const Doctor* doctor = dynamic_cast<const Doctor*>(allEmployee[i]))
		{
			cout << "Doctors: "<<*doctor << endl;

		}
		else if (const Referee* referee = dynamic_cast<const Referee*>(allEmployee[i]))
		{
			cout << "Referee: " << *referee << endl;
		}
		else if (const Judge* judge = dynamic_cast<const Judge*>(allEmployee[i]))
		{
			cout << "Judge: " << *judge << endl;

		}
	}
	typename vector<Boxer*>::const_iterator itr = allBoxers.begin();
	typename vector<Boxer*>::const_iterator itrEnd = allBoxers.end();
	for (; itr != itrEnd; ++itr)
		cout << "Boxer: " << **itr << endl;

	
}

Organization& Organization::operator = (const Organization& other)
{
	if (this == &other)
		return *this;

	allDoctors.clear();
	allBoxers.clear();
	 allReferees.clear();
	 allJudges.clear();

	//init all the arrays
	allDoctors.reserve(MaxnumOfDoctors);
	allBoxers.reserve(MaxnumOfBoxers);
	allReferees.reserve(MaxnumOfReferees);
	allJudges.reserve(MaxnumOfJudges);
	

	for (int i = 0; i < MaxnumOfDoctors; ++i)
		allDoctors[i] = new Doctor(*(other.allDoctors[i]));

	for (int i = 0; i < MaxnumOfBoxers; ++i)
		allBoxers[i] = new Boxer(*(other.allBoxers[i]));

	for (int i = 0; i < MaxnumOfReferees; ++i)
		allReferees[i] = new Referee(*(other.allReferees[i]));

	for (int i = 0; i < MaxnumOfJudges; ++i)
		allJudges[i] = new Judge(*(other.allJudges[i]));

	name= other.name;


	return *this;
}

const Organization& Organization::operator = (Organization&& other) noexcept
{
	if (this == &other)
		return *this;

	allDoctors.clear();
	allBoxers.clear();
	allReferees.clear();
	allJudges.clear();

	numOfLeagues = other.numOfLeagues;
	numOfBoxers = other.numOfBoxers;
	numOfReferees = other.numOfReferees;
	numOfDoctors = other.numOfDoctors;
	numOfJudges = other.numOfJudges;

	MaxnumOfLeagues = other.MaxnumOfLeagues;
	MaxnumOfBoxers = other.MaxnumOfBoxers;
	MaxnumOfReferees = other.MaxnumOfReferees;
	MaxnumOfDoctors = other.MaxnumOfDoctors;
	MaxnumOfJudges = other.MaxnumOfJudges;

	allDoctors = other.allDoctors;
	//allLeagues = other.allLeagues;
	allBoxers = other.allBoxers;
	allReferees = other.allReferees;
	allJudges = other.allJudges;
	LeagueNodeList = other.LeagueNodeList;

	// Reset the other object
	other.numOfLeagues = 0;
	other.numOfBoxers = 0;
	other.numOfReferees = 0;
	other.numOfDoctors = 0;
	other.numOfJudges = 0;

	other.MaxnumOfLeagues = 0;
	other.MaxnumOfBoxers = 0;
	other.MaxnumOfReferees = 0;
	other.MaxnumOfDoctors = 0;
	other.MaxnumOfJudges = 0;

	other.allDoctors.clear();
	other.allBoxers.clear();
	other.allReferees.clear();
	other.allJudges.clear();
	

	return *this;
}

bool Organization::operator == (const Organization& other) const
{
	return (this->name== other.name);
}

const Organization& Organization::operator += (League& p)
{
	addLeague(p);
	return *this;
}

const Organization& Organization::operator += (const Boxer& p)
{
	addBoxer(p);
	return *this;
}



const Organization& Organization::operator += (const Doctor& p)
{
	addDoctor(p);
	return *this;
}

const Organization& Organization::operator += (const Judge& p)
{
	addJudge(p);
	return *this;
}


