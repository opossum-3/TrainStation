#include "PassengerInfo.h"



PassengerInfo::PassengerInfo(const BasicString& destination, bool isFoodIncluded, 
							 unsigned baggageKg, double distance) :
							 destination(destination), isFoodIncluded(isFoodIncluded), 
							 baggageKg(baggageKg), distance(distance)
{

}

const BasicString& PassengerInfo::getDestination() const
{
	return destination;
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
