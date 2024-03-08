#define _CRT_SECURE_NO_WARNINGS
#include "Location.h"
#include <string>

Location::Location(const string address, int capacity, bool hasParking)  :
	capacity(capacity), has_Parking(has_Parking)
{
	setAddress(address);
}

Location::Location(const Location& location) :
	capacity(location.capacity), has_Parking(location.has_Parking)
{
	setAddress(location.address);
}

Location::Location(Location&& location) noexcept :
	capacity(location.capacity), has_Parking(location.has_Parking)
{
	setAddress(location.address);
	
}


void Location::setCapacity(int capacity)
{
	this->capacity = capacity;
}

void Location::setParking(bool Hasparking)
{
	this->has_Parking = Hasparking;
}

void Location::setAddress(const string address)
{
	this->address = address;
}

const string Location::getAddress() const
{
	return address;
}

int Location::getCapacity() const
{
	return capacity;
}

bool Location::hasParking() const
{
	return this->has_Parking;
}

std::ostream& operator<<(std::ostream& out, const Location& location)
{
	out << "Address: " << location.address << ", Capacity: " << location.capacity;
	out << ", Has Parking: " << (location.has_Parking ? "Yes" : "No");
	return out;
}

Location& Location::operator=(const Location& pre)
{
	if (this != &pre)
	{
		setAddress(pre.address);
		capacity = pre.capacity;
		has_Parking = pre.has_Parking;
	}

	return *this;
}

const Location& Location::operator=(Location&& pre) noexcept
{ // moving con
	if (this != &pre)
	{
		setAddress(pre.address);
		capacity = pre.capacity;
		has_Parking = pre.has_Parking;
	}

	return *this;
}

bool Location::operator==(const Location& other) const
{
	return (address== other.address) && (capacity == other.capacity) &&
		(has_Parking == other.has_Parking);
}