#include "Wagon.h"

Wagon::Wagon() : wagonId(0), basePrice(0), seats()
{

}

Wagon::~Wagon()
{

}

bool Wagon::isValidSeat(size_t seatId) const
{
	if (seatId == 0)
	{
		return false;
	}
	return seatId - 1 < seats.getSize();
}

void Wagon::reserveSeat(size_t seatId)
{
	if (!isValidSeat(seatId))
	{
		throw std::exception("Invalid seat ID!");
	}
	if (seats[seatId - 1])
	{
		throw std::exception("Seat already reserved!");
	}
	seats[seatId - 1] = true;
}

void Wagon::serialize(std::ofstream& ofstr) const
{
	if (!ofstr.is_open())
	{
		throw std::exception("File error!");
	}
	ofstr.write(reinterpret_cast<const char*>(&wagonId), sizeof(wagonId));
	ofstr.write(reinterpret_cast<const char*>(&basePrice), sizeof(basePrice));
	size_t count = seats.getSize();
	ofstr.write(reinterpret_cast<const char*>(&count), sizeof(count));
	for (size_t i = 0; i < count; i++)
	{
		ofstr.write(reinterpret_cast<const char*>(&seats[i]), sizeof(seats[i]));
	}
}

void Wagon::deserialize(std::ifstream& ifstr)
{
	if (!ifstr.is_open())
	{
		throw std::exception("File error!");
	}
	ifstr.read(reinterpret_cast<char*>(&wagonId), sizeof(wagonId));
	ifstr.read(reinterpret_cast<char*>(&basePrice), sizeof(basePrice));
	size_t count = 0;
	ifstr.read(reinterpret_cast<char*>(&count), sizeof(count));
	for (size_t i = 0; i < count; i++)
	{
		bool seat = false;
		ifstr.read(reinterpret_cast<char*>(&seat), sizeof(seat));
		seats.push_back(seat);
	}
}

bool Wagon::isEmpty() const
{
	size_t count = seats.getSize();
	for (size_t i = 0; i < count; i++)
	{
		if (seats[i])
		{
			return false;
		}
	}
	return true;
}

Wagon::Wagon(unsigned wagonId, unsigned basePrice) : wagonId(wagonId), 
													 basePrice(basePrice)
{
	
}

unsigned Wagon::getWagonId() const
{
	return wagonId;
}

size_t Wagon::getSeatCount() const
{
	return seats.getSize();
}

void Wagon::printSeats(size_t rows) const
{
	size_t count = seats.getSize();
	size_t cols = count / rows;
	size_t space = cols * 2 + (cols - 1);
	
	// Extra space for Sleep Wagon
	if (cols == 1)
	{
		space += 2;
	}
	std::cout << ' ';
	for (size_t i = 0; i < space; i++)
	{
		std::cout << '_';
	}
	std::cout << std::endl;

	for (size_t i = 0; i < rows; i++)
	{
		// Printing seat row
		std::cout << '|';
		for (size_t j = 0; j < cols; j++)
		{
			if (cols == 1)
			{
				std::cout << ' ';
			}
			size_t index = i * cols + j;
			if (seats[index])
			{
				std::cout << "XX";
			}
			else
			{
				printSeatNum(index + 1);
			}

			if (j < cols - 1 || cols == 1)
			{
				std::cout << ' ';
			}
		}
		std::cout << '|' << std::endl;

		// Printing empty row
		std::cout << '|';
		if (i < rows - 1)
		{
			for (size_t i = 0; i < space; i++)
			{
				std::cout << ' ';
			}
		}
		else
		{
			for (size_t i = 0; i < space; i++)
			{
				std::cout << '_';
			}
		}
		std::cout << '|' << std::endl;
	}
}

void Wagon::printSeatNum(size_t number) const
{
	if (number < 10)
	{
		std::cout << '0' << number;
	}
	else if (number < 100)
	{
		std::cout << number;
	}
}

void Wagon::clearSeats()
{
	size_t count = seats.getSize();
	for (size_t i = 0; i < count; i++)
	{
		seats[i] = false;
	}
}
