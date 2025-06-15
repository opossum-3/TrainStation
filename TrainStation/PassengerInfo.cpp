#include "PassengerInfo.h"



PassengerInfo::PassengerInfo(bool isFoodIncluded, unsigned baggageKg, double distance) :
							 isFoodIncluded(isFoodIncluded), baggageKg(baggageKg), distance(distance)
{

}

bool PassengerInfo::getFoodIncluded() const
{
	return isFoodIncluded;
}

unsigned PassengerInfo::getBaggageKg() const
{
	return baggageKg;
}

double PassengerInfo::getDistance() const
{
	return distance;
}
