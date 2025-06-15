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
	double getDistance() const;
	void print() const;
	void printWagon(unsigned wagonId) const;
	void addFirstClassWagon(unsigned basePrice, double comfortFactor);
	void addSecondClassWagon(unsigned basePrice, unsigned pricePerKg);
	void addSleepWagon(unsigned basePrice, unsigned pricePer100km);
	void removeWagon(unsigned wagonId);
	Wagon* findWagon(unsigned wagonId);
	const Wagon* findWagon(unsigned wagonId) const;
private:
	unsigned trainId;
	TrainMoment departure;
	TrainMoment arrival;
	double distance;
	double speed;
	BasicVector<Wagon*> wagons;
	unsigned currentWagonId;

	void copy(const Train& other);
	void free();
};