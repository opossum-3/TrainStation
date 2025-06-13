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