#include "Train.h"
#include "Station.h"

Train::Train()
{

}

Train::Train(unsigned id, const TrainMoment& departure, const TrainMoment& arrival, 
			 double distance, double speed) 
			 : trainId(id), departure(departure), arrival(arrival),
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
}

void Train::copy(const Train& other)
{
	trainId = other.trainId;
	departure = other.departure;
	arrival = other.arrival;
	distance = other.distance;
	speed = other.speed;
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
