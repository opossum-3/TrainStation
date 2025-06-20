#pragma once
#include <ctime>
#include "BasicString.h"

class Station;
class TrainMoment
{
public:
	TrainMoment();
	TrainMoment(Station* station, unsigned track, time_t time);
	Station* getStation() const;
	unsigned getTrack() const;
	time_t getTime() const;
	BasicString getFormattedTime() const;
	void serialize(std::ofstream& ofstr) const;
	void deserialize(std::ifstream& ifstr);
private:
	Station* station;
	unsigned track;
	time_t time;
};