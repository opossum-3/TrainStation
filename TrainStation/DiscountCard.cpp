#include "DiscountCard.h"

DiscountCard::DiscountCard(const BasicString& personName, unsigned cardId) : 
						   personName(personName), cardId(cardId)
{
	if (cardId < 100000 || cardId > 999999)
	{
		throw std::exception("Card ID should be 6-digit!");
	}
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
