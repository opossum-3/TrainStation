#include "DiscountCard.h"

DiscountCard::DiscountCard(const BasicString& personName, unsigned cardId) : 
						   personName(personName), cardId(cardId)
{

}

DiscountCard::~DiscountCard()
{

}

const BasicString& DiscountCard::getName() const
{
	return personName;
}

unsigned DiscountCard::getId() const
{
	return cardId;
}
