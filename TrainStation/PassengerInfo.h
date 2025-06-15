#pragma once

class PassengerInfo
{
public:
	PassengerInfo(bool isFoodIncluded, unsigned baggageKg, double distance);
	bool getFoodIncluded() const;
	unsigned getBaggageKg() const;
	double getDistance() const;
private:
	bool isFoodIncluded;
	unsigned baggageKg;
	double distance;
};