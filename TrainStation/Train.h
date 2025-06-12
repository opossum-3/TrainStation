#pragma once
#include "BasicVector.hpp"
#include "Wagon.h"
#include "TrainMoment.h";

class Station;
class Train
{
public:
	Train();
	Train(unsigned id, TrainMoment departure, TrainMoment arrival,
		 double distance, double speed);
	const TrainMoment& getDeparture() const;
	const TrainMoment& getArrival() const;
private:
	unsigned trainId;
	TrainMoment departure;
	TrainMoment arrival;
	double distance;
	double speed;
	BasicVector<Wagon*> wagons;
};