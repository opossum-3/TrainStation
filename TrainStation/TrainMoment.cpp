#include "TrainMoment.h"
#include "BasicString.h"
#include "TimeInterval.h"
#include "Station.h"

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

BasicString TrainMoment::getFormattedTime() const
{
    return TimeInterval::getFormattedTime(time);
}

void TrainMoment::serialize(std::ofstream& ofstr) const
{
    if (!ofstr.is_open())
    {
        throw std::exception("File error!");
    }
    BasicString stationName = station->getName();
    stationName.serialize(ofstr);
    ofstr.write(reinterpret_cast<const char*>(&track), sizeof(track));
    ofstr.write(reinterpret_cast<const char*>(&time), sizeof(time));
}

void TrainMoment::deserialize(std::ifstream& ifstr)
{
    if (!ifstr.is_open())
    {
        throw std::exception("File error!");
    }
    BasicString stationName;
    stationName.deserialize(ifstr);
    ifstr.read(reinterpret_cast<char*>(&track), sizeof(track));
    ifstr.read(reinterpret_cast<char*>(&time), sizeof(time));
}
