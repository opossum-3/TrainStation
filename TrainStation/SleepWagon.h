#pragma once
#include "Wagon.h"

class SleepWagon : public Wagon
{
public:
	SleepWagon();
	SleepWagon(unsigned wagonId, unsigned basePrice, unsigned pricePer100km);
	double getPrice(const PassengerInfo& info) const override;
	size_t getSeatCount() const override;
	void print() const override;
	BasicString getType() const override;
	void serialize(std::ofstream& ofstr) const override;
	void deserialize(std::ifstream& ifstr) override;
	Wagon* clone() override;
private:
	unsigned pricePer100km;
	size_t getRowsCount() const override;
};