#pragma once
#include <iostream>
using namespace std;

class Location
{
public:
	Location( const string address, int capacity, bool hasParking);

	Location(const Location& location);
	Location(Location&& location)noexcept;
	void setCapacity(int capacity);
	void setParking(bool parking);
	
	const string getAddress() const ;
	int getCapacity() const ;
	bool hasParking() const ;

	friend ostream& operator << (ostream& out, const Location& location);

	Location& operator = (const Location& pre);
	const Location& operator = (Location&& pre) noexcept;
	bool operator == (const Location& other) const;

private:
	 string address;
	int capacity;
	bool has_Parking;

	void setAddress(const string address);
};
