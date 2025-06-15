#pragma once
#include "BasicString.h"

class PassengerInfo
{
public:
	PassengerInfo(const BasicString& destination, bool isFoodIncluded, unsigned baggageKg, double distance);
	const BasicString& getDestination() const;
	bool getFoodIncluded() const;
	unsigned getBaggageKg() const;
	double getDistance() const;
private:
	BasicString destination;
	bool isFoodIncluded;
	unsigned baggageKg;
	double distance;
};