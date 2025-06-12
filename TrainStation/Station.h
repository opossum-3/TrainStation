#pragma once
#include "BasicString.h"
#include "BasicVector.hpp"
#include "Train.h"

class Station
{
public:
	Station();
	Station(BasicString name);
	void printSchedule() const;
private:
	BasicString name;
	BasicVector<Train> departureTrains;
	BasicVector<Train*> arrivingTrains;
};