#pragma once
#include <iostream>
using namespace std;
#include <string>
class Broadcast
{
public:
	Broadcast(const string description, const string channel, double duration);

	Broadcast(const Broadcast& broadcast);
	Broadcast(Broadcast&& broadcast) noexcept;

	void setDescription(const string description);
	void setDuration(double duration);
	
	const string getDescription()const;
	const string getChannel()const;
	double getDuration()const;

	friend ostream& operator << (ostream& out, const Broadcast& broadcast);

	Broadcast& operator = (const Broadcast& pre);
	const Broadcast& operator = (Broadcast&& pre)noexcept;

	bool operator == (const Broadcast& other) const;

private:
	string description;
	string channel;
	double duration;

	void setChannel(const string channel);
};
