#pragma once
#include "DiscountCard.h"

class DistanceCard : public DiscountCard
{
public:
	DistanceCard(const BasicString& personName, unsigned distance, unsigned cardId);
	double getDiscount(double price, const PassengerInfo& info) const override;
	unsigned getDistance() const;
private:
	BasicString route;
	unsigned distance;
};