#include "CardManager.h"
#include <iomanip>

CardManager* CardManager::manager;

CardManager* CardManager::instance()
{
	if (manager)
	{
		return manager;
	}
	manager = new CardManager();
	return manager;
}

void CardManager::createAgeCard(const BasicString& personName, unsigned age, const BasicString& file)
{
	AgeCard card(personName, age, currentCardId++);
	std::ofstream ofstr(file.getStr());
	saveAgeCard(ofstr, card);
	ofstr.close();
	std::cout << "Age card created successfully in file: " << file << std::endl;
}

void CardManager::createRouteCard(const BasicString& personName, 
	const BasicString& route, const BasicString& file)
{
	RouteCard card(personName, route, currentCardId++);
	std::ofstream ofstr(file.getStr());
	saveRouteCard(ofstr, card);
	ofstr.close();
	std::cout << "Route card created successfully in file: " << file << std::endl;
}

void CardManager::createDistanceCard(const BasicString& personName, 
	unsigned distance, const BasicString& file)
{
	DistanceCard card(personName, distance, currentCardId++);
	std::ofstream ofstr(file.getStr());
	saveDistanceCard(ofstr, card);
	ofstr.close();
	std::cout << "Distance card created successfully in file: " << file << std::endl;
}

CardManager::CardManager() : currentCardId(100000)
{
	
}

void CardManager::saveAgeCard(std::ofstream& ofstr, const AgeCard& card)
{
	checkFile(ofstr);
	BasicString header("|===Age card===|");
	size_t width = header.getLength();
	ofstr << header << std::endl;

	ofstr << "| " << std::left << std::setw(width - 3) << card.getName() << '|' << std::endl;

	ofstr << "| " << card.getAge();
	ofstr << std::left << std::setw(width - BasicString::getNumLength(card.getAge()) - 3);
	ofstr << " years old" << '|' << std::endl;

	ofstr << "| " << std::left << std::setw(width - 3) << card.getId() << '|' << std::endl;

	ofstr << "|==============|";
}

void CardManager::saveRouteCard(std::ofstream& ofstr, const RouteCard& card)
{
	checkFile(ofstr);
	BasicString header("|===Route card===|");
	size_t width = header.getLength();
	ofstr << header << std::endl;

	ofstr << "| " << std::left << std::setw(width - 3) << card.getName() << '|' << std::endl;

	ofstr << "| " << std::left << std::setw(width - 3) << card.getRoute() << '|' << std::endl;

	ofstr << "| " << std::left << std::setw(width - 3) << card.getId() << '|' << std::endl;

	ofstr << "|================|";
}

void CardManager::saveDistanceCard(std::ofstream& ofstr, const DistanceCard& card)
{
	checkFile(ofstr);
	BasicString header("|===Distance card===|");
	size_t width = header.getLength();
	ofstr << header << std::endl;

	ofstr << "| " << std::left << std::setw(width - 3) << card.getName() << '|' << std::endl;

	ofstr << "| " << card.getDistance();
	ofstr << std::left << std::setw(width - BasicString::getNumLength(card.getDistance()) - 3);
	ofstr << " km" << '|' << std::endl;

	ofstr << "| " << std::left << std::setw(width - 3) << card.getId() << '|' << std::endl;

	ofstr << "|===================|";
}

void CardManager::checkFile(std::ofstream& ofstr)
{
	if (!ofstr.is_open())
	{
		throw std::exception("File error!");
	}
}