#pragma once
#include "BasicVector.hpp"
#include "Station.h"
#include "Admin.h"

class TrainSystem
{
public:
	static TrainSystem* instance();
	TrainSystem(const TrainSystem& other) = delete;
	void start();

	void moveWagon(unsigned int sourceTrainId, unsigned int destinationTrainId, unsigned int wagonId);

	void buyTicket(BasicString& command, int& readIndex, unsigned int trainId, 
		unsigned int wagonId, unsigned int seatId, BasicString& ticketFile);
	void buyTicketDiscount(BasicString& command, int& readIndex, 
		unsigned int trainId, unsigned int wagonId, 
		unsigned int seatId, BasicString& ticketFile,
		BasicString& cardFile);
	static void free();
private:
	static TrainSystem* system;
	TrainSystem();
	BasicVector<Station> stations;
	BasicVector<Admin> admins;
	Admin* loggedAdmin;
	unsigned currentTrainId;

	void loadAdmins();
	void checkForCommandEnd(const BasicString& command, int& readIndex);
	void checkForAdmin();
	void loginAdmin(BasicString& username, BasicString& password);

	void addStation(BasicString& name);
	void addTrain(BasicString& station, BasicString& destination,
				  double distance, double speed, time_t departureTime);
	void addWagon(unsigned trainId, BasicString& wagonType, BasicString& command, int& readIndex, unsigned basePrice);
	
	void removeTrain(unsigned id);
	void removeWagon(unsigned trainId, unsigned wagonId);

	void printStations() const;
	void printSchedule(const BasicString& stationName) const;
	void printScheduleDestination(const BasicString& stationName, const BasicString& destinationName) const;
	void printScheduleTime(const BasicString& stationName, time_t time) const;
	void printTrain(unsigned id) const;
	void printWagon(unsigned trainId, unsigned wagonId) const;

	unsigned getMaxTrainId() const;

	Station* findStation(BasicString& name);
	Train* findTrain(unsigned id);
	const Train* findTrain(unsigned id) const;
};