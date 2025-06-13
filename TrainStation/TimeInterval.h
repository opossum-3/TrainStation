#pragma once
#include <ctime>

class TimeInterval
{
public:
	TimeInterval();
	TimeInterval(const TimeInterval& other);
	TimeInterval(time_t from, time_t to);
	bool isInInterval(time_t time) const;
	bool intersectsWith(const TimeInterval& other) const;
private:
	time_t start;
	time_t end;
};