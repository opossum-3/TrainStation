#pragma once
#include "BasicVector.hpp"

enum class WagonType { Null, FirstClass, SecondClass, SleepWagon };
class Wagon
{
public:
	Wagon();
	Wagon(unsigned wagonId, unsigned basePrice);
	unsigned getWagonId() const;
	virtual size_t getSeatCount() const = 0;
	virtual unsigned getPrice() const = 0;
	virtual void print() const = 0;
protected:
	unsigned wagonId;
	unsigned basePrice;
	BasicVector<bool> seats;

	void printSeats(size_t rows) const;
	virtual size_t getRowsCount() const = 0;
	void printSeatNum(size_t number) const;
	void clearSeats();
};