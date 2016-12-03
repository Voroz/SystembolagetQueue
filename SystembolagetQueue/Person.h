#pragma once
#include <string>


struct Person
{
public:
	Person(std::string name, int arrivalTime, int serveTime) :
		name(name)
		, arrivalTime(arrivalTime)
		, serveTime(serveTime) {

	}
	Person() {

	}

	bool operator>(const Person& otherPerson) const{
		return (arrivalTime > otherPerson.arrivalTime);
	}
	
	std::string name = "";
	int arrivalTime;
	int serveTime;
};

