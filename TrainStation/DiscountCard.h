#pragma once
#include "BasicString.h"
#include "PassengerInfo.h"

class DiscountCard
{
public:
	DiscountCard(const BasicString& personName, unsigned cardId);
	virtual double getDiscount(double price, const PassengerInfo& info) const = 0;
	virtual ~DiscountCard();
	const BasicString& getName() const;
	unsigned getId() const;
private:
	BasicString personName;
	unsigned cardId;
};