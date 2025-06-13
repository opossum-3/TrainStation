#pragma once
#include "BasicVector.hpp"
#include "Wagon.h"
#include "TrainMoment.h";

class Station;
class Train
{
public:
	Train();
	Train(unsigned id, const TrainMoment& departure, const TrainMoment& arrival,
		 double distance, double speed);
	Train(const Train& other);
	Train& operator= (const Train& other);
	~Train();
	unsigned getId() const;
	const TrainMoment& getDeparture() const;
	const TrainMoment& getArrival() const;
	void print() const;
private:
	unsigned trainId;
	TrainMoment departure;
	TrainMoment arrival;
	double distance;
	double speed;
	BasicVector<Wagon*> wagons;

	void copy(const Train& other);
	void free();
};