#include "AgeCard.h"

AgeCard::AgeCard(const BasicString& personName, unsigned age, unsigned cardId) : 
                 DiscountCard(personName, cardId), age(age)
{

}

double AgeCard::getDiscount(double price, const PassengerInfo& info) const
{
    if (age <= 10)
    {
        return price;
    }
    if (age <= 18)
    {
        return 0.5 * price;
    }
    return 0.2 * price;
}
