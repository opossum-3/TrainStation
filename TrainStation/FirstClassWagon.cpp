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

double FirstClassWagon::getPrice(const PassengerInfo& info) const
{
	return basePrice * comfortFactor + (info.getFoodIncluded() ? 10 : 0);
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

void FirstClassWagon::serialize(std::ofstream& ofstr) const
{
	if (!ofstr.is_open())
	{
		throw std::exception("File error!");
	}
	BasicString type = getType();
	type.serialize(ofstr);
	Wagon::serialize(ofstr);
	ofstr.write(reinterpret_cast<const char*>(&foodIncluded), sizeof(foodIncluded));
	ofstr.write(reinterpret_cast<const char*>(&comfortFactor), sizeof(comfortFactor));
}

void FirstClassWagon::deserialize(std::ifstream& ifstr)
{
	Wagon::deserialize(ifstr);
	ifstr.read(reinterpret_cast<char*>(&foodIncluded), sizeof(foodIncluded));
	ifstr.read(reinterpret_cast<char*>(&comfortFactor), sizeof(comfortFactor));
}

Wagon* FirstClassWagon::clone()
{
	FirstClassWagon* wagon = new FirstClassWagon(wagonId, basePrice, comfortFactor);
	return wagon;
}

size_t FirstClassWagon::getRowsCount() const
{
	return 5;
}
