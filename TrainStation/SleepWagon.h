#pragma once
#include "Wagon.h"

class SleepWagon : public Wagon
{
public:
	SleepWagon();
	SleepWagon(unsigned wagonId, unsigned basePrice, unsigned pricePer100km);
	unsigned getPrice() const override;
	size_t getSeatCount() const override;
	void print() const override;
	BasicString getType() const override;
private:
	unsigned pricePer100km;
	size_t getRowsCount() const override;
};