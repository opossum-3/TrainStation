#include "Ticket.h"
#include "TimeInterval.h"
#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstring>

Ticket::Ticket(Train* train, Wagon* wagon, unsigned seatId, double discount, double price)
{
	TrainMoment departure = train->getDeparture();
	TrainMoment arrival = train->getArrival();
	departureStation = departure.getStation()->getName();
	arrivalStation = arrival.getStation()->getName();
	trainId = train->getId();
	wagonId = wagon->getWagonId();
	this->seatId = seatId;
	departureTime = departure.getTime();
	arrivalTime = arrival.getTime();
	departurePlatform = departure.getTrack();
	this->discount = discount;
	this->price = price;
}

void Ticket::writeToFile(const BasicString& file)
{
	std::ofstream ofstr(file.getStr(), std::ios::trunc);
	if (!ofstr.is_open())
	{
		throw std::exception("File error!");
	}
	BasicString header("|===========Train Ticket===========|");
	size_t width = header.getLength();
	ofstr << header << std::endl;
	ofstr << "| Ticket: " << departureStation;
	ofstr << " - " << std::left << std::setw(width - departureStation.getLength() - 14);
	ofstr << arrivalStation << '|' << std::endl;

	ofstr << "| Train ID: " << std::left << std::setw(width - 13) << trainId << '|' << std::endl;
	ofstr << "| Wagon ID: " << std::left << std::setw(width - 13) << wagonId << '|' << std::endl;
	ofstr << "| Seat ID: " << std::left << std::setw(width - 12) << seatId << '|' << std::endl;

	ofstr << "| Departure time: " << std::left << std::setw(width - 19);
	ofstr << TimeInterval::getFormattedTime(departureTime) << '|' << std::endl;

	ofstr << "| Arrival time: " << std::left << std::setw(width - 17);
	ofstr << TimeInterval::getFormattedTime(arrivalTime) << '|' << std::endl;

	ofstr << "| Departure platform: " << std::left << std::setw(width - 23);
	ofstr << departurePlatform + 1 << '|' << std::endl;

	ofstr << "| Discount: " << std::setprecision(2) << discount;
	ofstr << std::left << std::setw(width - getLength((size_t)discount) - 13);
	ofstr << " lv." << '|' << std::endl;

	ofstr << "| Price: " << std::setprecision(2) << price;
	ofstr << std::left << std::setw(width - getLength((size_t)price) - 10);
	ofstr << " lv." << '|' << std::endl;

	ofstr << "|==================================|";
	ofstr.close();
}

size_t Ticket::getLength(size_t num) const
{
	if (num < 10)
	{
		return 1;
	}
	return getLength(num / 10) + 1;
}
