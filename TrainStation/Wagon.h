#pragma once
#include "BasicVector.hpp"
#include "BasicString.h";
#include "PassengerInfo.h"

enum class WagonType { Null, FirstClass, SecondClass, SleepWagon };
class Wagon
{
public:
	Wagon();
	Wagon(unsigned wagonId, unsigned basePrice);
	unsigned getWagonId() const;
	virtual size_t getSeatCount() const = 0;
	virtual double getPrice(const PassengerInfo& info) const = 0;
	virtual void print() const = 0;
	virtual BasicString getType() const = 0;
	virtual ~Wagon();
	bool isValidSeat(size_t seat) const;
	void reserveSeat(size_t seat);
	virtual void serialize(std::ofstream& ofstr) const;
	virtual void deserialize(std::ifstream& ifstr);
	bool isEmpty() const;
protected:
	unsigned wagonId;
	unsigned basePrice;
	BasicVector<bool> seats;

	void printSeats(size_t rows) const;
	virtual size_t getRowsCount() const = 0;
	void printSeatNum(size_t number) const;
	void clearSeats();
};