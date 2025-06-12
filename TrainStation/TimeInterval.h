#pragma once
#include <ctime>

class TimeInterval
{
public:
	TimeInterval();
	TimeInterval(time_t from, time_t to);
	bool isInInterval(time_t time) const;
private:
	time_t start;
	time_t end;
};