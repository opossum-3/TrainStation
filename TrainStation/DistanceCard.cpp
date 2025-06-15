#include "DistanceCard.h"

DistanceCard::DistanceCard(const BasicString& personName, unsigned distance, unsigned cardId) :
                           DiscountCard(personName, cardId), distance(distance)
{

}

double DistanceCard::getDiscount(double price, const PassengerInfo& info) const
{
    if (info.getDistance() <= distance)
    {
        return 0.5 * price;
    }
    return 0.3 * price;
}
