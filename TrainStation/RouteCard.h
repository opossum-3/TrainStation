#pragma once
#include "DiscountCard.h"

class RouteCard : public DiscountCard
{
public:
	RouteCard(const BasicString& personName, const BasicString& route, unsigned cardId);
	double getDiscount(double price, const PassengerInfo& info) const override;
private:
	BasicString route;
};