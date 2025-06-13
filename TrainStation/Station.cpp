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

void Station::addTrain(unsigned trainId, Station* destination, 
					   double distance, double speed, time_t departureTime)
{
	double travelHours = distance / speed;
	time_t arrivalTime = departureTime + travelHours * 3600;
	TimeInterval interval(departureTime, arrivalTime);
	TrainMoment departure(this, getFreeTrack(interval), departureTime);
	TrainMoment arrival(destination, destination->getFreeTrack(interval), arrivalTime);
	
	Train train(trainId, departure, arrival, distance, speed);
	departureTrains.push_back(train);
	Train* last = &departureTrains[departureTrains.getSize() - 1];
	destination->arrivingTrains.push_back(last);
}

unsigned Station::getMaxTrainId() const
{
	unsigned max = 0;
	size_t count = departureTrains.getSize();
	for (size_t i = 0; i < count; i++)
	{
		unsigned current = departureTrains[i].getId();
		if (current > max)
		{
			max = current;
		}
	}
	return max;
}

unsigned Station::getFreeTrack(const TimeInterval& interval)
{
	size_t count = tracks.getSize();
	for (size_t i = 0; i < count; i++)
	{
		if (tracks[i].isFreeInterval(interval))
		{
			tracks[i].addInterval(interval);
			return i;
		}
	}
	Track track;
	track.addInterval(interval);
	tracks.push_back(track);
	return count;
}

const Train* Station::findTrain(unsigned trainId) const
{
	size_t count = departureTrains.getSize();
	for (size_t i = 0; i < count; i++)
	{
		if (departureTrains[i].getId() == trainId)
		{
			return &(departureTrains[i]);
		}
	}
	return nullptr;
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
