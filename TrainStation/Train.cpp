#include "Train.h"
#include "Station.h"
#include "FirstClassWagon.h"
#include "SecondClassWagon.h"
#include "SleepWagon.h"

Train::Train()
{

}

Train::Train(unsigned id, const TrainMoment& departure, const TrainMoment& arrival, 
			 double distance, double speed) 
			 : trainId(id), currentWagonId(1), departure(departure), arrival(arrival),
			   distance(distance), speed(speed), wagons()
{
	
}

Train::Train(const Train& other)
{
	copy(other);
}

Train& Train::operator=(const Train& other)
{
	if (this != &other)
	{
		free();
		copy(other);
	}
	return *this;
}

Train::~Train()
{
	free();
}

unsigned Train::getId() const
{
	return trainId;
}

const TrainMoment& Train::getDeparture() const
{
	return departure;
}

const TrainMoment& Train::getArrival() const
{
	return arrival;
}

double Train::getDistance() const
{
	return distance;
}

void Train::print() const
{
	std::cout << "===Train ID: " << trainId << "===" << std::endl;
	std::cout << "Starting Station: " << departure.getStation()->getName() << std::endl;
	std::cout << "Destination: " << arrival.getStation()->getName() << std::endl;
	std::cout << "Distance: " << distance << "km" << std::endl;
	std::cout << "Speed: " << speed << "km/h" << std::endl;
	std::cout << "Departure Time: " << departure.getFormattedTime() << std::endl;
	std::cout << "Arrival Time: " << arrival.getFormattedTime() << std::endl;
	std::cout << "Departure Platform: " << departure.getTrack() + 1 << std::endl;

	std::cout << std::endl << "Wagons: " << std::endl;
	size_t count = wagons.getSize();
	for (size_t i = 0; i < count; i++)
	{
		std::cout << wagons[i]->getWagonId() << " - " << wagons[i]->getType() << std::endl;
	}
}

void Train::printWagon(unsigned wagonId) const
{
	size_t count = wagons.getSize();
	for (size_t i = 0; i < count; i++)
	{
		if (wagons[i]->getWagonId() == wagonId)
		{
			wagons[i]->print();
		}
	}
}

void Train::addFirstClassWagon(unsigned basePrice, double comfortFactor)
{
	FirstClassWagon* wagon = new FirstClassWagon(currentWagonId++, basePrice, comfortFactor);
	wagons.push_back(wagon);
	std::cout << "Added First Class Wagon with ID: " << currentWagonId - 1 << std::endl;
}

void Train::addSecondClassWagon(unsigned basePrice, unsigned pricePerKg)
{
	SecondClassWagon* wagon = new SecondClassWagon(currentWagonId++, basePrice, pricePerKg);
	wagons.push_back(wagon);
	std::cout << "Added Second Class Wagon with ID: " << currentWagonId - 1 << std::endl;
}

void Train::addSleepWagon(unsigned basePrice, unsigned pricePer100km)
{
	SleepWagon* wagon = new SleepWagon(currentWagonId++, basePrice, pricePer100km);
	wagons.push_back(wagon);
	std::cout << "Added Sleep Wagon with ID: " << currentWagonId - 1 << std::endl;
}

void Train::addWagon(Wagon* wagon)
{
	if (!wagon)
	{
		throw std::exception("Invalid argument!");
	}
	wagons.push_back(wagon);
}

void Train::removeWagon(unsigned wagonId)
{
	size_t count = wagons.getSize();
	for (size_t i = 0; i < count; i++)
	{
		if (wagons[i]->getWagonId() == wagonId)
		{
			delete[] wagons[i];
			wagons.removeAt(i);
			std::cout << "Wagon removed successfully." << std::endl;
			return;
		}
	}
	throw std::exception("Invalid wagon ID!");
}

Wagon* Train::findWagon(unsigned wagonId)
{
	size_t count = wagons.getSize();
	for (size_t i = 0; i < count; i++)
	{
		if (wagons[i]->getWagonId() == wagonId)
		{
			return wagons[i];
		}
	}
	return nullptr;
}

const Wagon* Train::findWagon(unsigned wagonId) const
{
	size_t count = wagons.getSize();
	for (size_t i = 0; i < count; i++)
	{
		if (wagons[i]->getWagonId() == wagonId)
		{
			return wagons[i];
		}
	}
	return nullptr;
}

void Train::serialize(std::ofstream& ofstr) const
{
	if (!ofstr.is_open())
	{
		throw std::exception("File error!");
	}
	ofstr.write(reinterpret_cast<const char*>(&trainId), sizeof(trainId));

}

void Train::deserialize(std::ifstream& ifstr)
{
	if (!ifstr.is_open())
	{
		throw std::exception("File error!");
	}
	ifstr.read(reinterpret_cast<char*>(&trainId), sizeof(trainId));

}

void Train::copy(const Train& other)
{
	trainId = other.trainId;
	departure = other.departure;
	arrival = other.arrival;
	distance = other.distance;
	speed = other.speed;
	currentWagonId = other.currentWagonId;
	size_t count = other.wagons.getSize();
	for (size_t i = 0; i < count; i++)
	{
		wagons.push_back(other.wagons[i]);
	}
}

void Train::free()
{
	size_t count = wagons.getSize();
	for (size_t i = 0; i < count; i++)
	{
		delete[] wagons[i];
	}
}
