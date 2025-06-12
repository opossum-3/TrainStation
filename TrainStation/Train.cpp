#include "Train.h"

Train::Train()
{

}

Train::Train(unsigned id, TrainMoment departure, TrainMoment arrival, 
			 double distance, double speed) 
			 : trainId(id), departure(departure), arrival(arrival),
			   distance(distance), speed(speed), wagons()
{
	
}

const TrainMoment& Train::getDeparture() const
{
	return departure;
}

const TrainMoment& Train::getArrival() const
{
	return arrival;
}


