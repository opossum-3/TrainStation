#include "CardManager.h"
#include "CommandReader.h"
#include <iomanip>

CardManager* CardManager::manager;
const int INPUT_BUFFER_SIZE = 35;

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
	validCardList.push_back(card.getId());
	std::cout << "Age card created successfully in file: " << file << std::endl;
}

void CardManager::createRouteCard(const BasicString& personName, 
	const BasicString& route, const BasicString& file)
{
	RouteCard card(personName, route, currentCardId++);
	std::ofstream ofstr(file.getStr());
	saveRouteCard(ofstr, card);
	ofstr.close();
	validCardList.push_back(card.getId());
	std::cout << "Route card created successfully in file: " << file << std::endl;
}

void CardManager::createDistanceCard(const BasicString& personName, 
	unsigned distance, const BasicString& file)
{
	DistanceCard card(personName, distance, currentCardId++);
	std::ofstream ofstr(file.getStr());
	saveDistanceCard(ofstr, card);
	ofstr.close();
	validCardList.push_back(card.getId());
	std::cout << "Distance card created successfully in file: " << file << std::endl;
}

double CardManager::getDiscount(const BasicString& cardFile, double price, const PassengerInfo& info)
{
	std::ifstream ifstr(cardFile.getStr());
	if (!ifstr.is_open())
	{
		throw std::exception("File error!");
	}
	char buffer[INPUT_BUFFER_SIZE];
	ifstr.getline(buffer, INPUT_BUFFER_SIZE);
	BasicString line(buffer);
	if (line.equals("|===Age card===|"))
	{
		AgeCard* card = loadAgeCard(ifstr);
		if (!isValidCard(card->getId()))
		{
			throw std::exception("Invalid discount card!");
		}
		double discount = card->getDiscount(price, info);
		ifstr.close();
		delete[] card;
		return discount;
	}
	if (line.equals("|===Route card===|"))
	{
		RouteCard* card = loadRouteCard(ifstr);
		double discount = card->getDiscount(price, info);
		ifstr.close();
		delete[] card;
		return discount;
	}
	if (line.equals("|==Distance card==|"))
	{
		DistanceCard* card = loadDistanceCard(ifstr);
		double discount = card->getDiscount(price, info);
		ifstr.close();
		delete[] card;
		return discount;
	}
	throw std::exception("Invalid discount card file!");
	return 0;
}

CardManager::CardManager() : currentCardId(100000), validCardList()
{
	loadValidCardList();
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
	BasicString header("|==Distance card==|");
	size_t width = header.getLength();
	ofstr << header << std::endl;

	ofstr << "| " << std::left << std::setw(width - 3) << card.getName() << '|' << std::endl;

	ofstr << "| " << card.getDistance();
	ofstr << std::left << std::setw(width - BasicString::getNumLength(card.getDistance()) - 3);
	ofstr << " km" << '|' << std::endl;

	ofstr << "| " << std::left << std::setw(width - 3) << card.getId() << '|' << std::endl;

	ofstr << "|=================|";
}

void CardManager::saveValidCardList()
{
	std::ofstream ofstr("validCardList.txt", std::ios::trunc);
	checkFile(ofstr);
	size_t count = validCardList.getSize();
	ofstr << count << std::endl;
	for (size_t i = 0; i < count; i++)
	{
		ofstr << validCardList[i] << std::endl;
	}
	ofstr.close();
}

void CardManager::free()
{
	delete manager;
}

AgeCard* CardManager::loadAgeCard(std::ifstream& ifstr)
{
	char buffer[INPUT_BUFFER_SIZE];
	int readIndex = 2;
	ifstr.getline(buffer, INPUT_BUFFER_SIZE);
	BasicString line(buffer);
	BasicString name = CommandReader::readName(line, readIndex);

	readIndex = 2;
	ifstr.getline(buffer, INPUT_BUFFER_SIZE);
	line = BasicString(buffer);
	unsigned age = CommandReader::readUnsigned(line, readIndex);

	readIndex = 2;
	ifstr.getline(buffer, INPUT_BUFFER_SIZE);
	line = BasicString(buffer);
	unsigned cardId = CommandReader::readUnsigned(line, readIndex);

	return new AgeCard(name, age, cardId);
}

RouteCard* CardManager::loadRouteCard(std::ifstream& ifstr)
{
	char buffer[INPUT_BUFFER_SIZE];
	int readIndex = 2;
	ifstr.getline(buffer, INPUT_BUFFER_SIZE);
	BasicString line(buffer);
	BasicString name = CommandReader::readName(line, readIndex);

	readIndex = 2;
	ifstr.getline(buffer, INPUT_BUFFER_SIZE);
	line = BasicString(buffer);
	BasicString route = CommandReader::readName(line, readIndex);

	readIndex = 2;
	ifstr.getline(buffer, INPUT_BUFFER_SIZE);
	line = BasicString(buffer);
	unsigned cardId = CommandReader::readUnsigned(line, readIndex);

	return new RouteCard(name, route, cardId);
}

DistanceCard* CardManager::loadDistanceCard(std::ifstream& ifstr)
{
	char buffer[INPUT_BUFFER_SIZE];
	int readIndex = 2;
	ifstr.getline(buffer, INPUT_BUFFER_SIZE);
	BasicString line(buffer);
	BasicString name = CommandReader::readName(line, readIndex);

	readIndex = 2;
	ifstr.getline(buffer, INPUT_BUFFER_SIZE);
	line = BasicString(buffer);
	unsigned distance = CommandReader::readUnsigned(line, readIndex);

	readIndex = 2;
	ifstr.getline(buffer, INPUT_BUFFER_SIZE);
	line = BasicString(buffer);
	unsigned cardId = CommandReader::readUnsigned(line, readIndex);

	return new DistanceCard(name, distance, cardId);
}

void CardManager::loadValidCardList()
{
	std::ifstream ifstr("validCardList.txt");
	if (!ifstr.is_open())
	{
		return;
	}
	size_t count = 0;
	ifstr >> count;
	for (size_t i = 0; i < count; i++)
	{
		unsigned cardId = 0;
		ifstr >> cardId;
		validCardList.push_back(cardId);
	}
	ifstr.close();
}

void CardManager::checkFile(std::ofstream& ofstr)
{
	if (!ofstr.is_open())
	{
		throw std::exception("File error!");
	}
}

bool CardManager::isValidCard(unsigned cardId)
{
	size_t count = validCardList.getSize();
	for (size_t i = 0; i < count; i++)
	{
		if (validCardList[i] == cardId)
		{
			return true;
		}
	}
	return false;
}
