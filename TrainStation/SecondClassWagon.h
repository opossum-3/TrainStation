#pragma once
#include "Wagon.h"

class SecondClassWagon : public Wagon
{
public:
	SecondClassWagon();
	SecondClassWagon(unsigned wagonId, unsigned basePrice, unsigned pricePerKg);
	double getPrice(const PassengerInfo& info) const override;
	size_t getSeatCount() const override;
	void print() const override;
	BasicString getType() const override;
	void serialize(std::ofstream& ofstr) const override;
	void deserialize(std::ifstream& ifstr) override;
	Wagon* clone() override;
private:
	unsigned pricePerKg;
	size_t getRowsCount() const override;
};