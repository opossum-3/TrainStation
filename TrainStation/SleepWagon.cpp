#include "SleepWagon.h"

SleepWagon::SleepWagon() : Wagon(), pricePer100km(0)
{

}

SleepWagon::SleepWagon(unsigned wagonId, unsigned basePrice, 
					   unsigned pricePer100km) : Wagon(wagonId, basePrice), 
					   pricePer100km(pricePer100km)
{
	seats = BasicVector<bool>(getSeatCount());
	clearSeats();
}

double SleepWagon::getPrice(const PassengerInfo& info) const
{
	return basePrice + info.getDistance() / 100 * pricePer100km;
}

size_t SleepWagon::getSeatCount() const
{
	return 5;
}

void SleepWagon::print() const
{
	std::cout << "=== Wagon ID: " << wagonId << " ===" << std::endl;
	std::cout << "WagonType: Sleep Wagon" << std::endl;
	std::cout << "Base Price: " << basePrice << " lv." << std::endl;
	std::cout << "Price per 100 km: " << pricePer100km << " lv." << std::endl;
	std::cout << "Seats: " << getSeatCount() << std::endl;
	std::cout << "Available seats:" << std::endl;
	printSeats(getRowsCount());
	std::cout << std::endl;
}

BasicString SleepWagon::getType() const
{
	return BasicString("Sleep Wagon");
}

size_t SleepWagon::getRowsCount() const
{
	return 5;
}

