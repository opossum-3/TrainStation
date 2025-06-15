#pragma once
#include "BasicString.h";
#include "AgeCard.h"
#include "RouteCard.h"
#include "DistanceCard.h"
#include <fstream>

class CardManager
{
public:
	static CardManager* instance();
	CardManager(const CardManager& other) = delete;
	void createAgeCard(const BasicString& personName, unsigned age, const BasicString& file);
	void createRouteCard(const BasicString& personName, const BasicString& route, const BasicString& file);
	void createDistanceCard(const BasicString& personName, unsigned distance, const BasicString& file);
private:
	CardManager();
	static CardManager* manager;
	unsigned currentCardId;
	void saveAgeCard(std::ofstream& ofstr, const AgeCard& card);
	void checkFile(std::ofstream& ofstr);
	void saveRouteCard(std::ofstream& ofstr, const RouteCard& card);
	void saveDistanceCard(std::ofstream& ofstr, const DistanceCard& card);
};