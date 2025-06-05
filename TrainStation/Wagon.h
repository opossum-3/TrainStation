#pragma once
#include "BasicVector.hpp"

class Wagon
{
public:
	Wagon();
	Wagon(unsigned wagonId, unsigned basePrice, size_t seatCount);
	unsigned getWagonId() const;
	size_t getSeatCount() const;
	virtual unsigned getPrice() const = 0;
protected:
	unsigned wagonId;
	unsigned basePrice;
	BasicVector<bool> seats;
};