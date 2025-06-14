#include "FirstClassWagon.h"

FirstClassWagon::FirstClassWagon() : Wagon(), comfortFactor(0)
{

}


FirstClassWagon::FirstClassWagon(unsigned wagonId, unsigned basePrice, 
								 double comfortFactor):
								 Wagon(wagonId, basePrice),
								 foodIncluded(foodIncluded), comfortFactor(comfortFactor)
{									
	seats = BasicVector<bool>(getSeatCount());
	clearSeats();
}

unsigned FirstClassWagon::getPrice() const
{
	return basePrice;
}

size_t FirstClassWagon::getSeatCount() const
{
	return 10;
}

void FirstClassWagon::print() const
{
	std::cout << "=== Wagon ID: " << wagonId << " ===" << std::endl;
	std::cout << "WagonType: First Class" << std::endl;
	std::cout << "Base Price: " << basePrice << " lv." << std::endl;
	std::cout << "Comfort Factor: " << comfortFactor << std::endl;
	std::cout << "Seats: " << getSeatCount() << std::endl;
	std::cout << "Available seats:" << std::endl;
	printSeats(getRowsCount());
	std::cout << std::endl;
}

BasicString FirstClassWagon::getType() const
{
	return BasicString("First Class");
}

size_t FirstClassWagon::getRowsCount() const
{
	return 5;
}
