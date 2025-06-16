#pragma once
#include "Wagon.h"
#include "BasicString.h"

class FirstClassWagon : public Wagon
{
public:
	FirstClassWagon();
	FirstClassWagon(unsigned wagonId, unsigned basePrice, double comfortFactor);
	double getPrice(const PassengerInfo& info) const override;
	size_t getSeatCount() const override;
	void print() const override;
	BasicString getType() const override;
	void serialize(std::ofstream& ofstr) const override;
	void deserialize(std::ifstream& ifstr) override;
	Wagon* clone() override;
private:
	bool foodIncluded;
	double comfortFactor;
	size_t getRowsCount() const override;
};