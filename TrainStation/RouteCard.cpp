#include "RouteCard.h"

RouteCard::RouteCard(const BasicString& personName, const BasicString& route, unsigned cardId) :
                     DiscountCard(personName, cardId), route(route)
{
}

double RouteCard::getDiscount(double price, const PassengerInfo& info) const
{
    if (info.getDestination() == route)
    {
        return price;
    }
    return 0;
}

const BasicString& RouteCard::getRoute() const
{
    return route;
}
