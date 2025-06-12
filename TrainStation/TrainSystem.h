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

	void loadAdmins();
};