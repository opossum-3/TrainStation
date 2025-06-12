#pragma once
#include "BasicVector.hpp"
#include "Station.h"

class TrainSystem
{
public:
	TrainSystem(const TrainSystem& other) = delete;
	static TrainSystem* instance();
	static TrainSystem* system;
private:
	TrainSystem();
	BasicVector<Station> stations;
};