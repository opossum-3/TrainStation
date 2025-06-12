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
	void printStations() const;
private:
	static TrainSystem* system;
	TrainSystem();
	BasicVector<Station> stations;
	BasicVector<Admin> admins;
	Admin* loggedAdmin;
	void loadAdmins();
	void checkForCommandEnd(BasicString command, int& readIndex);
	void loginAdmin(BasicString& username, BasicString& password);
	void checkForAdmin();
};