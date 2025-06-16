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

double SecondClassWagon::getPrice(const PassengerInfo& info) const
{
	return basePrice + info.getBaggageKg() * pricePerKg;
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

void SecondClassWagon::serialize(std::ofstream& ofstr) const
{
	if (!ofstr.is_open())
	{
		throw std::exception("File error!");
	}
	BasicString type = getType();
	type.serialize(ofstr);
	Wagon::serialize(ofstr);
	ofstr.write(reinterpret_cast<const char*>(&pricePerKg), sizeof(pricePerKg));
}

void SecondClassWagon::deserialize(std::ifstream& ifstr)
{
	Wagon::deserialize(ifstr);
	ifstr.read(reinterpret_cast<char*>(&pricePerKg), sizeof(pricePerKg));
}

Wagon* SecondClassWagon::clone()
{
	SecondClassWagon* wagon = new SecondClassWagon(wagonId, basePrice, pricePerKg);
	return wagon;
}

size_t SecondClassWagon::getRowsCount() const
{
	return 5;
}

