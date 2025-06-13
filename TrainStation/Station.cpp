#include "Station.h"
#include <iostream>
#include <iomanip>

const char* Station::arrivalHeaders[] = {"Arrival Time", "Arrival Platform",
		"Train ID", "Starting station" , "Status" };

size_t Station::arrivalTableWidths[] = { 20, 20, 12, 16, 14 };

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

	// Print header
	size_t tableWidth = getTableWidth(arrivalTableWidths, 5);
	BasicString line = BasicString::repeat('-', tableWidth);
	std::cout << line << std::endl;
	std::cout << "| ";
	for (size_t i = 0; i < 5; i++)
	{
		std::cout << std::left << std::setw(arrivalTableWidths[i]);
		std::cout << arrivalHeaders[i] << " | ";
	}
	std::cout << std::endl;
	std::cout << line << std::endl;

	// Print data
	size_t count = arrivingTrains.getSize();
	for (size_t i = 0; i < count; i++)
	{
		std::cout << "| ";
		const TrainMoment& departure = arrivingTrains[i]->getDeparture();
		const TrainMoment& arrival = arrivingTrains[i]->getArrival();
		std::cout << std::left << std::setw(arrivalTableWidths[0]);
		std::cout << arrival.getFormattedTime() << " | ";
		std::cout << std::left << std::setw(arrivalTableWidths[1]);
		std::cout << arrival.getTrack() << " | ";
		std::cout << std::left << std::setw(arrivalTableWidths[2]);
		std::cout << arrivingTrains[i]->getId() << " | ";
		std::cout << std::left << std::setw(arrivalTableWidths[3]);
		std::cout << departure.getStation()->getName() << " | ";
		std::cout << std::left << std::setw(arrivalTableWidths[4]);
		time_t currentTime = time(0);
		std::cout << (currentTime >= arrival.getTime() ? "Arrived" : "To arrive") << " |";
		std::cout << std::endl;
	}
	std::cout << line << std::endl;
}

void Station::printDepartures() const
{

}

size_t Station::getTableWidth(size_t columnWidths[], size_t count) const
{
	size_t result = 0;
	for (size_t i = 0; i < count; i++)
	{
		result += columnWidths[i];
	}
	result += 3 * count + 1;
	return result;
}
