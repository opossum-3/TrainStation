#pragma once
#include "TimeInterval.h"
#include "BasicVector.hpp"

class Track
{
public:
	Track();
	void addInterval(time_t start, time_t end);
	bool isFree(time_t time) const;
private:
	BasicVector<TimeInterval> busyIntervals;
};