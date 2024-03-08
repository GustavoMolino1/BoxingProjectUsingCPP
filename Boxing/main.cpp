#define _CRT_SECURE_NO_WARNINGS

#include "Boxer.h"
#include "Employee.h"
#include "Doctor.h"
#include "Judge.h"
#include "Referee.h"
#include "Location.h"
#include "Broadcast.h"
#include "Organization.h"
#include "Championship.h"
#include "BoxingMatch.h"
#include "League.h"
#include "NodeLinked.h"

class Employee;
class Doctor;
class Judge;

const string getRandomName()
{
	// List of possible names
	const string names[] = { "Mike", "John", "Davd", "Sarh", "Emiy", "Danl", "Emma", "Ofia", "Jams", "Soph", "Wihm", "Adva", "Joeh", "gMia", "Bein", "Abil", "Jacb", "Elth", "Miel", "Grce", "Mark", "Luke", "Noah", "Paul", "Adam", "Anne", "Anna", "Rose", "Alex", "Kate", "Jack", "Mary", "Jane", "Lily", "Eric","popo","Lujo","Piji"};

	// Randomly select a name from the list
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> dis(0, sizeof(names) / sizeof(names[0]) - 1);
	int index = dis(gen);

	return names[index];
}
const char* getRandomNameEmployee()
{
	// List of possible names
	const char* names[] = { "John", "Alice", "Michael", "Sophia", "David", "Emma", "James", "Olivia", "Daniel", "Mia", "Alexander", "Ava", "William", "Charlotte", "Benjamin", "Amelia", "Elijah", "Harper", "Matthew", "Emily", "Joseph", "Abigail", "Samuel", "Elizabeth", "Henry", "Sofia", "Jackson", "Ella", "Sebastian", "Scarlett","Mike", "John", "Emily", "Michael", "Sophia", "David", "Olivia", "Daniel", "Emma" ,"Roy","Tomer","Yuval","Yogev", "John", "Davd", "Sarh", "Emiy", "Danl", "Emma", "Ofia", "Jams", "Soph", "Wihm", "Adva", "Joeh", "gMia", "Bein", "Abil", "Jacb", "Elth", "Miel", "Grce" };

	// Randomly select a name from the list
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> dis(0, sizeof(names) / sizeof(names[0]) - 1);
	int index = dis(gen);

	return names[index];
}


bool createDoctor(Organization & org)
{
	const int numberOfDoctor = 5;
	// Generate random values for name and age

	const int minAge = 25;
	const int maxAge = 60;
	for (size_t i = 0; i < numberOfDoctor; i++)
	{
		std::random_device rd;
		std::mt19937 gen(rd());
		std::uniform_int_distribution<int> ageDist(minAge, maxAge);
		const char* randomName = getRandomNameEmployee();
		int randomAge = ageDist(gen);
		// Generate other random values for specialty, yearsExperience, company, and salary if needed
		/*if (!org.addDoctor(Doctor(randomName, randomAge, "Legs", 10, "Teva", 5000.0)))
			return false;
		*/
		if (!org.addEmployee(Doctor(randomName, randomAge, "Legs", 10, "Teva", 5000.0)))
			return false;	
	}
	return true;
}


const char* PickUpRandomOrganizionName()
{
	// Generate random values for name, leagues, boxers, referees, doctors, and judges
	const char* names[] = { "UFC A", "ISRAEL BOXING", "USA BOXING C", "PTS Boxing", "RRTC Boxing" };
	const int numNames = sizeof(names) / sizeof(names[0]);


	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<int> nameDist(0, numNames - 1);
	const char* randomName = names[nameDist(gen)];

	return randomName;
	
	
}

bool AddAndCreateBoxers(Organization & org)
{
	const int NUM_BOXERS = org.getMaxnumOfBoxers();


	// Generate random boxers with names
	for (int i = 0; i < NUM_BOXERS; i++)
	{
		const string name = getRandomName();
		double weight = 60.0 + (rand() % 41); // Random weight between 60.0 and 100.0
		int wins = rand() % 50;
		int losses = rand() % 50;
		int experience = rand() % 10;
		bool injured = (rand() % 2) == 1;
		bool inMatch = (rand() % 2) == 1;

		org.addBoxer(Boxer(name, 20, "sdf", weight, experience));
	}
	return true;
}

bool createRandomJudge(Organization &org)
{
	int const numberofJudges = org.getMaxnumOfJudges();


	const char* companies[] = { "Company A", "Company B", "Company C", "Company D" };
	const int numCompanies = 4;
	for (int i = 0; i < numberofJudges; i++)
	{
		const char* randomName = getRandomNameEmployee();
		int randomAge = rand() % 30 + 30; // Random age between 30 and 59
		int randomYearsOfExperience = rand() % 20 + 1; // Random years of experience between 1 and 20
		const char* randomCompany = companies[rand() % numCompanies];
		double randomSalary = static_cast<double>(rand() % 5000) / 100.0 + 50.0;
		// Random salary between 50.00 and 99.99

	/*	if (!org.addJudge(Judge(randomName, randomAge, randomYearsOfExperience, randomCompany, randomSalary)))
			return false;
			*/
		if (!org.addEmployee(Judge(randomName, randomAge, randomYearsOfExperience, randomCompany, randomSalary)))
			return false;
	}
	return true;
}
Location createRandomLocation()
{
	const char* addresses[] = {
	"123 Main Street, Stadium City",
	"456 Park Avenue, Arena Town",
	"789 Elm Street, Colosseum Village",
	"321 Oak Avenue, Ring City",
	"987 Maple Drive, Boxingville",
	"654 Pine Road, Arena Heights",
	"543 Cedar Lane, Stadium Springs",
	"876 Walnut Court, Ringfield",
	"234 Birch Avenue, Boxingborough",
	"768 Willow Street, Stadiumville"
	};
	const int numAddresses = 4;
	const int maxCapacity =50000;
	const int minCapacity = 10000;

	const char* randomAddress = addresses[rand() % numAddresses];
	int randomCapacity = rand() % (maxCapacity - minCapacity + 1) + minCapacity;
	bool randomHasParking = rand() % 2 == 0; // Randomly true or false

	return Location(randomAddress, randomCapacity, randomHasParking);
}

Broadcast createRandomBroadcast()
{
	const char* descriptions[] = { "Sports", "Boxing"};
	const char* channels[] = { "Channel A", "Channel B", "Channel C", "Channel D" };
	const int numDescriptions = 2;
	const int numChannels = 4;
	const double maxDuration = 120.0;
	const double minDuration = 30.0;

	const char* randomDescription = descriptions[rand() % numDescriptions];
	const char* randomChannel = channels[rand() % numChannels];
	double randomDuration = (double)(rand()) / RAND_MAX * (maxDuration - minDuration) + minDuration;

	return Broadcast(randomDescription, randomChannel, randomDuration);
}

Championship createRandomChampionship()
{
	const char* names[] = { "World Championship", "International Championship", "National Championship", "Regional Championship" };
	const int numNames = 4;
	const int maxPrize = 100000;
	const int minPrize = 10000;

	const char* randomName = names[rand() % numNames];
	int randomPrize = rand() % (maxPrize - minPrize + 1) + minPrize;

	return Championship(randomName, randomPrize);
}

bool createRandomReferee(Organization & org)
{
	
	const char* names[] = { "John", "Alice", "Michael", "Sophia", "David", "Emma", "James", "Olivia", "Daniel", "Mia", "Alexander", "Ava", "William", "Charlotte", "Benjamin", "Amelia", "Elijah", "Harper", "Matthew", "Emily", "Joseph", "Abigail", "Samuel", "Elizabeth", "Henry", "Sofia", "Jackson", "Ella", "Sebastian", "Scarlett" };
	const int numNames = sizeof(names) / sizeof(names[0]);
	const char* specialities[] = { "Kickboxing", "Boxing", "MMA", "Muay Thai", "Judo" };
	const int numSpecialities = 5;
	const int maxYearsOfExperience = 20;
	const int minYearsOfExperience = 1;
	const char* companies[] = { "Referee Association", "Sports Federation", "International Referee League" };
	const int numCompanies = 3;
	const double maxSalary = 10000.0;
	const double minSalary = 1000.0;
	for (size_t i = 0; i < org.getMaxnumOfReferees(); i++)
	{


		const string randomName = getRandomName();//names[rand() % numNames];
		int randomAge = rand() % 40 + 20;
		const char* randomSpeciality = specialities[rand() % numSpecialities];
		int randomYearsOfExperience = rand() % (maxYearsOfExperience - minYearsOfExperience + 1) + minYearsOfExperience;
		const char* randomCompany = companies[rand() % numCompanies];
		double randomSalary = (double)(rand() % (int)((maxSalary - minSalary) * 100 + 1)) / 100.0 + minSalary;
		
		//if (!org.addreferee(Referee(randomName, randomAge, randomSpeciality, randomYearsOfExperience, randomCompany, randomSalary)))return false;
		if (!org.addEmployee(Referee(randomName, randomAge, randomSpeciality, randomYearsOfExperience, randomCompany, randomSalary)))
			return false;
	}
	return true;
}

void menu()
{
	std::cout << "----- Main Menu -----" << std::endl;
	//std::cout << "1. Create Organization" << std::endl;
	std::cout << "2. Add Boxers to Organization" << std::endl;
	std::cout << "3. Add Referee & judge" << std::endl;
	std::cout << "4. Add Doctor" << std::endl;
	std::cout << "5. Create Championship" << std::endl;
	std::cout << "6. Create Random Location" << std::endl;
	std::cout << "7. Create Random Broadcast" << std::endl;
	std::cout << "8. Create League" << std::endl;
	std::cout << "9. Generate League And Print Information." << std::endl;
	std::cout << "10. Exit" << std::endl;
	std::cout << "---------------------" << std::endl;
	std::cout << "Enter your choice: ";
}
int main()
{
	/*NodeLinked<Referee*>t; too show efrat that the remove works. 
	t.add(new Referee("Tomer", 12, "REW", 12, "Boo", 10000));
	t.add(new Referee("REMOVE!!!", 12, "qwe", 12, "Boo", 10000));
	t.add(new Referee("Tomeqweqwer", 12, "qweqw", 12, "Boo", 10000));
	t.add(new Referee("Tomeqweqweqer", 12, "eqeq", 12, "Boo", 10000));
	t.print();
	t.remove(t.get(1));
	t.print();*/


	int choice;
	bool exitMenu = false;
	
	Organization *org = Organization::getInstance(PickUpRandomOrganizionName());

	Championship* champ = nullptr;
	Boxer** myleagueBoxer = nullptr;//org.getBoxerPerLeague();
	Doctor** legdoctor = nullptr; //org.getDoctorsPerLeague();
	Doctor* firstDoctor = nullptr;//legdoctor[0];;
	Judge** legjudge = nullptr;// org.getJudgePerLeague();
	Referee** legreferee = nullptr; //org.getRefereePerLeague();
	Location* loc = nullptr; //new Location(createRandomLocation());
	Broadcast* brod = nullptr;// new Broadcast(createRandomBroadcast());
	League* myLeague = nullptr;
	while (!exitMenu)
	{
		menu();
		std::cin >> choice;

		switch (choice)
		{
		case 2:
			// Add Boxers to Organization logic
			std::cout << "Adding Boxers to Organization..." << std::endl;
			AddAndCreateBoxers(*org);
			break;
		case 3:
			// Add Referee and judge  logic
			std::cout << "Adding Referee and Judge..." << std::endl;
			createRandomJudge(*org);
			createRandomReferee(*org);
			
			break;
		case 4:
			// Add Doctor logic
			std::cout << "Adding Doctor..." << std::endl;
			createDoctor(*org);
		
			
			break;
		case 5:
			// Create Championship logic
			std::cout << "Creating Championship..." << std::endl;
			champ = new Championship(createRandomChampionship());
			break;
		case 6:
			// Create Random Location logic
			std::cout << "Creating Random Location..." << std::endl;
			loc = new Location(createRandomLocation());
			
			break;
		case 7:
			// Create Random Broadcast logic
			std::cout << "Creating Random Broadcast..." << std::endl;
			
			 brod = new Broadcast(createRandomBroadcast());
			break;
		case 8:
			// Create League logic
			std::cout << "Creating League..." << std::endl;
			if (champ == nullptr || loc == nullptr || brod == nullptr) {
				std::cout << "Error: Invalid parameters. Cannot create League." << std::endl;
			}
			else {
			
				myLeague = new League("Champion League", Boxer::eCategory::HEAVY_WEIGHT, *loc, *brod, *champ);
				org->addLeague(*myLeague);
			}

			break;
		case 9:
			// Generate League logic
			std::cout << " Trying Generating League..." << std::endl;
			if ( org->getNumOfBoxers() > 0) {
				myleagueBoxer = org->getBoxerPerLeague();
				// Access the myleagueBoxer array
			}
			else {
				std::cout << "No boxers available." << std::endl;
				// Handle the case when there are no boxers
				break;
			}
			if (org->getNumOfDoctors() > 0) {
				legdoctor = org->getDoctorsPerLeague();
				firstDoctor = legdoctor[0];
				// Access the legdoctor array and firstDoctor
			}
			else {
				std::cout << "No doctors available." << std::endl;
				// Handle the case when there are no doctors
				break;
			}
			if (org->getNumOfJudges() > 0) {
				legjudge = org->getJudgePerLeague();
				// Access the legjudge array
			}
			else {
				std::cout << "No judges available." << std::endl;
				// Handle the case when there are no judges
				break;
			}
			if (org->getNumOfReferees() > 0) {
				legreferee = org->getRefereePerLeague();
				// Access the legreferee array
			}
			else {
				std::cout << "No referees available." << std::endl;
				// Handle the case when there are no referees
				break;
			}
			if (myLeague != NULL) {
				myLeague->addDoctor(legdoctor);
				myLeague->addBoxers(myleagueBoxer);
				myLeague->addReferee(legreferee);
				myLeague->genarateBracketAndPrint(myleagueBoxer);
				cout << *myLeague << endl;
			}
			break;
		case 10:
			//myLeague->printBoxerLeaggue();
			// Exit program
			org->PrintAllEmployee();
			exitMenu = true;
			std::cout << "Exiting..." << std::endl;
			
			break;
		default:
			std::cout << "Invalid choice. Please try again." << std::endl;
			break;
		}

		std::cout << std::endl;
	}
	

	return 0;
}
	
