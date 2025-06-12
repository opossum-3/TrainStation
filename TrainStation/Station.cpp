#include "Station.h"
#include <iostream>

Station::Station()
{

}

Station::Station(BasicString name) : name(name)
{

}

const BasicString& Station::getName() const
{
	return name;
}

void Station::printSchedule() const
{
	printArrivals();
	std::cout << std::endl;
	printDepartures();
}

void Station::printArrivals() const
{
	std::cout << "Arrivals: " << std::endl;
	BasicString line = BasicString::repeat('-', 70);
	std::cout << line;
	std::cout << "| Arrival Time        | Arrival Platform | Train ID ";
	std::cout << "| Starting station | Status  |" << std::endl;
	std::cout << line;

}

void Station::printDepartures() const
{

}
