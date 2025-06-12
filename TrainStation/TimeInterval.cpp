#include "TimeInterval.h"

TimeInterval::TimeInterval() : start(0), end(0)
{

}

TimeInterval::TimeInterval(time_t start, time_t end) : start(start), end(end)
{

}

bool TimeInterval::isInInterval(time_t time) const
{
	return time >= start && time <= end;
}
