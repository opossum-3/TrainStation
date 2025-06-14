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
	void printScheduleDestination(const Station* destination) const;
	void printScheduleTime(time_t time) const;
	void addTrain(unsigned trainId, Station* destination,
				  double distance, double speed, time_t departureTime);
	bool tryRemoveTrain(unsigned trainId);
	unsigned getMaxTrainId() const;
	unsigned getFreeTrack(const TimeInterval& interval);
	const Train* findTrain(unsigned trainId) const;
	Train* findTrain(unsigned trainId);
private:
	BasicString name;
	BasicVector<Track> tracks;
	BasicVector<Train> departureTrains;
	BasicVector<Train*> arrivingTrains;

	static const char* arrivalHeaders[];
	static const char* departureHeaders[];
	static size_t arrivalTableWidths[];
	static size_t departureTableWidths[];

	void printArrivals() const;
	void printDepartures() const;
	void printDepartureHeader(const BasicString& line) const;
	void printDepartureRow(size_t i) const;
	size_t getTableWidth(size_t columnWidths[], size_t count) const;
};