#pragma once
#include <ctime>

class Station;
class TrainMoment
{
public:
	TrainMoment();
	TrainMoment(Station* station, unsigned track, time_t time);
	Station* getStation() const;
	unsigned getTrack() const;
	time_t getTime() const;
private:
	Station* station;
	unsigned track;
	time_t time;
};