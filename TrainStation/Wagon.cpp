#include "Wagon.h"

Wagon::Wagon() : wagonId(0), basePrice(0), seats()
{
	
}

Wagon::Wagon(unsigned wagonId, unsigned basePrice, size_t seatCount) : wagonId(wagonId), basePrice(basePrice)
{
	seats = BasicVector<bool>(seatCount);
}

unsigned Wagon::getWagonId() const
{
	return wagonId;
}

size_t Wagon::getSeatCount() const
{
	return seats.getSize();
}
