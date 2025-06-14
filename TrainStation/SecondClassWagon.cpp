#include "SecondClassWagon.h"

SecondClassWagon::SecondClassWagon() : Wagon(), pricePerKg(0)
{

}

SecondClassWagon::SecondClassWagon(unsigned wagonId, unsigned basePrice, unsigned pricePerKg) 
								 : Wagon(wagonId, basePrice), pricePerKg(pricePerKg)
{
	seats = BasicVector<bool>(getSeatCount());
	clearSeats();
}

unsigned SecondClassWagon::getPrice() const
{
	return basePrice;
}

size_t SecondClassWagon::getSeatCount() const
{
	return 20;
}

void SecondClassWagon::print() const
{
	std::cout << "=== Wagon ID: " << wagonId << " ===" << std::endl;
	std::cout << "WagonType: Second Class" << std::endl;
	std::cout << "Base Price: " << basePrice << " lv." << std::endl;
	std::cout << "Price for 1 kg luggage: " << pricePerKg << " lv." << std::endl;
	std::cout << "Seats: " << getSeatCount() << std::endl;
	std::cout << "Available seats:" << std::endl;
	printSeats(getRowsCount());
	std::cout << std::endl;
}

BasicString SecondClassWagon::getType() const
{
	return BasicString("Second Class");
}

size_t SecondClassWagon::getRowsCount() const
{
	return 5;
}

