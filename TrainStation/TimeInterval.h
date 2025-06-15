#pragma once
#include <ctime>
#include "BasicString.h"

class TimeInterval
{
public:
	TimeInterval();
	TimeInterval(const TimeInterval& other);
	TimeInterval(time_t from, time_t to);
	bool isInInterval(time_t time) const;
	bool intersectsWith(const TimeInterval& other) const;
	static BasicString getFormattedTime(time_t time);
private:
	time_t start;
	time_t end;
};