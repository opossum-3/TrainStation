#include "Track.h"

Track::Track() : busyIntervals()
{

}

void Track::addInterval(const TimeInterval& interval)
{
    busyIntervals.push_back(interval);
}

bool Track::isFree(time_t time) const
{
    size_t count = busyIntervals.getSize();
    for (size_t i = 0; i < count; i++)
    {
        if (busyIntervals[i].isInInterval(time))
        {
            return false;
        }
    }
    return true;
}

bool Track::isFreeInterval(const TimeInterval& interval) const
{
    size_t count = busyIntervals.getSize();
    for (size_t i = 0; i < count; i++)
    {
        if (busyIntervals[i].intersectsWith(interval))
        {
            return false;
        }
    }
    return true;
}
