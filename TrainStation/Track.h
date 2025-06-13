#pragma once
#include "TimeInterval.h"
#include "BasicVector.hpp"

class Track
{
public:
	Track();
	void addInterval(const TimeInterval& interval);
	bool isFree(time_t time) const;
	bool isFreeInterval(const TimeInterval& interval) const;
private:
	BasicVector<TimeInterval> busyIntervals;
};