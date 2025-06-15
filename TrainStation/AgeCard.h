#pragma once
#include "DiscountCard.h"

class AgeCard : public DiscountCard
{
public:
	AgeCard(const BasicString& personName, unsigned age, unsigned cardId);
	double getDiscount(double price, const PassengerInfo& info) const override;
	unsigned getAge() const;
private:
	unsigned age;
};