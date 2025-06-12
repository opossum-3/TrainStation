#include "TrainMoment.h"

TrainMoment::TrainMoment() : station(nullptr), track(0), time(0)
{

}

TrainMoment::TrainMoment(Station* station, unsigned track, time_t time)
{
    this->station = station;
    this->track = track;
    this->time = time;
}

Station* TrainMoment::getStation() const
{
    return station;
}

unsigned TrainMoment::getTrack() const
{
    return track;
}

time_t TrainMoment::getTime() const
{
    return time;
}
