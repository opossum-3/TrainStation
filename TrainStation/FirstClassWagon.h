#pragma once
#include "Wagon.h"
#include "BasicString.h"

class FirstClassWagon : public Wagon
{
public:
	FirstClassWagon();
	FirstClassWagon(unsigned wagonId, unsigned basePrice, double comfortFactor);
	unsigned getPrice() const override;
	size_t getSeatCount() const override;
	void print() const override;
	BasicString getType() const override;
private:
	bool foodIncluded;
	double comfortFactor;
	size_t getRowsCount() const override;
};