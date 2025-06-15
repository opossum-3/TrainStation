#pragma once
#include "BasicString.h"
#include "BasicVector.hpp"
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

	double getDiscount(const BasicString& cardFile, double price, const PassengerInfo& info);
	bool isValidCard(unsigned cardId);
	void saveValidCardList();
private:
	CardManager();
	static CardManager* manager;
	unsigned currentCardId;
	BasicVector<unsigned> validCardList;
	void checkFile(std::ofstream& ofstr);

	void saveAgeCard(std::ofstream& ofstr, const AgeCard& card);
	void saveRouteCard(std::ofstream& ofstr, const RouteCard& card);
	void saveDistanceCard(std::ofstream& ofstr, const DistanceCard& card);

	AgeCard* loadAgeCard(std::ifstream& ifstr);
	RouteCard* loadRouteCard(std::ifstream& ifstr);
	DistanceCard* loadDistanceCard(std::ifstream& ifstr);
	void loadValidCardList();
};