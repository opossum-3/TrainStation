#pragma once
#include <ctime>
#include "BasicString.h"
#include "Station.h"
#include "Train.h"
#include "Wagon.h"

class Ticket
{
public:
	Ticket(Train* train, Wagon* wagon, unsigned seatId, double discount, double price);
	void writeToFile(const BasicString& file);
private:
	BasicString departureStation;
	BasicString arrivalStation;

	unsigned trainId;
	unsigned wagonId;
	unsigned seatId;

	time_t departureTime;
	time_t arrivalTime;

	unsigned departurePlatform;

	double discount;
	double price;

	size_t getLength(size_t num) const;
};