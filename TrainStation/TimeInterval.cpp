#include "TimeInterval.h"

const int TIME_FORMAT_BUFFER_SIZE = 30;

TimeInterval::TimeInterval() : start(0), end(0)
{

}

TimeInterval::TimeInterval(const TimeInterval& other) : start(other.start), end(other.end)
{

}

TimeInterval::TimeInterval(time_t start, time_t end) : start(start), end(end)
{

}

bool TimeInterval::isInInterval(time_t time) const
{
	return time >= start && time <= end;
}

bool TimeInterval::intersectsWith(const TimeInterval& other) const
{
	if (isInInterval(other.start) || isInInterval(other.end))
	{
		return true;
	}
	if (other.isInInterval(start) || other.isInInterval(end))
	{
		return true;
	}
	return false;
}

BasicString TimeInterval::getFormattedTime(time_t time)
{
	tm timeData;
	localtime_s(&timeData, &time);
	char buffer[TIME_FORMAT_BUFFER_SIZE] = { 0 };
	strftime(buffer, TIME_FORMAT_BUFFER_SIZE, "%d/%m/%Y %H:%M", &timeData);
	return BasicString(buffer);
}
