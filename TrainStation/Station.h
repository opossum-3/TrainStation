#pragma once
#include "BasicString.h"
#include "BasicVector.hpp"
#include "Train.h"
#include "Track.h"

class Station
{
public:
	Station();
	Station(BasicString name);
	const BasicString& getName() const;
	void printSchedule() const;
private:
	BasicString name;
	BasicVector<Track> tracks;
	BasicVector<Train> departureTrains;
	BasicVector<Train*> arrivingTrains;
	void printArrivals() const;
	void printDepartures() const;
};