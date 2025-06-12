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
private:
	static TrainSystem* system;
	TrainSystem();
	BasicVector<Station> stations;
	BasicVector<Admin> admins;
	Admin* loggedAdmin;
	unsigned currentTrainId;

	void loadAdmins();
	void checkForCommandEnd(BasicString command, int& readIndex);
	void checkForAdmin();
	void loginAdmin(BasicString& username, BasicString& password);
	void addStation(BasicString& name);
	void printStations() const;
	unsigned getMaxTrainId() const;

	Station* findStation(BasicString& name);
};