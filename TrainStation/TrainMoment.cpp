#include "TrainMoment.h"
#include "BasicString.h"

const int TIME_FORMAT_BUFFER_SIZE = 30;

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
    tm timeData;
    localtime_s(&timeData, &time);
    char buffer[TIME_FORMAT_BUFFER_SIZE] = { 0 };
    strftime(buffer, TIME_FORMAT_BUFFER_SIZE, "%d/%m/%Y %H:%M", &timeData);
    return BasicString(buffer);
}
