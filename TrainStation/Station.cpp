#include "Station.h"
#include <iostream>
#include <iomanip>

const char* Station::arrivalHeaders[] = {"Arrival Time", "Arrival Platform",
		"Train ID", "Starting station" , "Status" };
const char* Station::departureHeaders[] = { "Departure Time", "Arrival Time",
		"Destination", "Departure Platform", "Train ID", "Status" };

size_t Station::arrivalTableWidths[] = { 20, 20, 12, 16, 14 };
size_t Station::departureTableWidths[] = { 20, 20, 16, 20, 12, 14 };

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
	std::cout << "Arrivals: " << std::endl;
	printArrivals();
	std::cout << std::endl;
	std::cout << "Departure: " << std::endl;
	printDepartures();
}

void Station::printScheduleDestination(const Station* destination) const
{
	if (!destination)
	{
		throw std::exception("Invalid destination!");
	}
	size_t tableWidth = getTableWidth(departureTableWidths, 6);
	BasicString line = BasicString::repeat('-', tableWidth);
	printDepartureHeader(line);
	size_t count = departureTrains.getSize();
	size_t filtered = 0;
	for (size_t i = 0; i < count; i++)
	{
		if (departureTrains[i].getArrival().getStation() == destination)
		{
			filtered++;
			printDepartureRow(i);
		}
	}
	if (filtered > 0)
	{
		std::cout << line << std::endl;
	}
}

void Station::printScheduleTime(time_t time) const
{
	size_t tableWidth = getTableWidth(departureTableWidths, 6);
	BasicString line = BasicString::repeat('-', tableWidth);
	printDepartureHeader(line);
	size_t count = departureTrains.getSize();
	size_t filtered = 0;
	for (size_t i = 0; i < count; i++)
	{
		if (departureTrains[i].getDeparture().getTime() >= time)
		{
			filtered++;
			printDepartureRow(i);
		}
	}
	if (filtered > 0)
	{
		std::cout << line << std::endl;
	}
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

bool Station::tryRemoveTrain(unsigned trainId)
{
	size_t count = departureTrains.getSize();
	for (size_t i = 0; i < count; i++)
	{
		if (departureTrains[i].getId() == trainId)
		{
			departureTrains.removeAt(i);
			return true;
		}
	}
	return false;
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

Train* Station::findTrain(unsigned trainId)
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
		std::cout << arrival.getTrack() + 1 << " | ";
		std::cout << std::left << std::setw(arrivalTableWidths[2]);
		std::cout << arrivingTrains[i]->getId() << " | ";
		std::cout << std::left << std::setw(arrivalTableWidths[3]);
		std::cout << departure.getStation()->getName() << " | ";
		std::cout << std::left << std::setw(arrivalTableWidths[4]);
		time_t currentTime = time(0);
		std::cout << (currentTime >= arrival.getTime() ? "Arrived" : "To arrive") << " |";
		std::cout << std::endl;
	}
	if (count > 0)
	{
		std::cout << line << std::endl;
	}
}

void Station::printDepartures() const
{
	size_t tableWidth = getTableWidth(departureTableWidths, 6);
	BasicString line = BasicString::repeat('-', tableWidth);
	printDepartureHeader(line);

	size_t count = departureTrains.getSize();
	for (size_t i = 0; i < count; i++)
	{
		printDepartureRow(i);
	}
	if (count > 0)
	{
		std::cout << line << std::endl;
	}
}

void Station::printDepartureHeader(const BasicString& line) const
{
	std::cout << line << std::endl;
	std::cout << "| ";
	for (size_t i = 0; i < 6; i++)
	{
		std::cout << std::left << std::setw(departureTableWidths[i]);
		std::cout << departureHeaders[i] << " | ";
	}
	std::cout << std::endl;
	std::cout << line << std::endl;
}

void Station::printDepartureRow(size_t i) const
{
	std::cout << "| ";
	const TrainMoment& departure = departureTrains[i].getDeparture();
	const TrainMoment& arrival = departureTrains[i].getArrival();
	std::cout << std::left << std::setw(departureTableWidths[0]);
	std::cout << departure.getFormattedTime() << " | ";
	std::cout << std::left << std::setw(departureTableWidths[1]);
	std::cout << arrival.getFormattedTime() << " | ";
	std::cout << std::left << std::setw(departureTableWidths[2]);
	std::cout << arrival.getStation()->getName() << " | ";
	std::cout << std::left << std::setw(departureTableWidths[3]);
	std::cout << departure.getTrack() + 1 << " | ";
	std::cout << std::left << std::setw(departureTableWidths[4]);
	std::cout << departureTrains[i].getId() << " | ";
	std::cout << std::left << std::setw(departureTableWidths[5]);
	time_t currentTime = time(0);
	std::cout << (currentTime >= departure.getTime() ? "Departed" : "To depart") << " |";
	std::cout << std::endl;
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
