#define _CRT_SECURE_NO_WARNINGS
#include "Broadcast.h"


Broadcast::Broadcast(const string description, const string channel, double duration)
	: duration(duration)
{

	setDescription(description);
	setChannel(channel);
}

Broadcast::Broadcast(const Broadcast& broadcast)
	: duration(broadcast.duration)
{
	setDescription(broadcast.description);
	setChannel(broadcast.channel);
}

Broadcast::Broadcast(Broadcast&& broadcast) noexcept
	: duration(broadcast.duration), description(broadcast.description), channel(broadcast.channel)
{
}



void Broadcast::setDescription(const string description)
{
	this->description = description;
}

void Broadcast::setDuration(double duration)
{
	this->duration = duration;
}

void Broadcast::setChannel(const string channel)
{
	this->channel = channel;
}


const string Broadcast::getDescription()const
{
	return description;
}

const string Broadcast::getChannel()const
{
	return channel;
}

double Broadcast::getDuration()const
{
	return duration;
}

ostream& operator<<(ostream& out, const Broadcast& broadcast)
{
	out << "Description: " << broadcast.description << ", Channel: " << broadcast.channel;
	out << ", Duration: " << broadcast.duration << " Enjoy watching the battle";
	return out;
}

Broadcast& Broadcast::operator=(const Broadcast& pre)
{
	if (this != &pre)
	{
		setDescription(pre.description);
		setChannel(pre.channel);
		duration = pre.duration;
	}
	return *this;
}

const Broadcast& Broadcast::operator=(Broadcast&& pre) noexcept
{
	if (this != &pre)
	{
		
		description = pre.description;
		channel = pre.channel;
		duration = pre.duration;

	}
	return *this;
}

bool Broadcast::operator==(const Broadcast& other) const
{
	return (description== other.description) && (channel== other.channel) &&
		(duration == other.duration);
}