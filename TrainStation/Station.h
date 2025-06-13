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
	void addTrain(unsigned trainId, Station* destination,
				  double distance, double speed, time_t departureTime);
	unsigned getMaxTrainId() const;
	unsigned getFreeTrack(const TimeInterval& interval);
	const Train* findTrain(unsigned trainId) const;
private:
	BasicString name;
	BasicVector<Track> tracks;
	BasicVector<Train> departureTrains;
	BasicVector<Train*> arrivingTrains;

	static const char* arrivalHeaders[]; 
	static size_t arrivalTableWidths[];

	void printArrivals() const;
	void printDepartures() const;
	size_t getTableWidth(size_t columnWidths[], size_t count) const;
};