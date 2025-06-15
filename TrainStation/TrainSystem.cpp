#include "TrainSystem.h"
#include "CommandReader.h"
#include "CardManager.h"
#include "Wagon.h"
#include "PassengerInfo.h"
#include "Ticket.h"
#include <fstream>
#include <iostream>
#include <ctime>

TrainSystem* TrainSystem::system;

TrainSystem::TrainSystem() : loggedAdmin(nullptr), currentTrainId(1000)
{

}

void TrainSystem::loadAdmins()
{
    std::ifstream ifstr("Admins.txt");
    if (!ifstr.is_open())
    {
        throw std::exception("File error!");
    }
    while(!ifstr.eof())
    {
        Admin admin;
        admin.deserialize(ifstr);
        admins.push_back(admin);
    }
    ifstr.close();
}

void TrainSystem::checkForCommandEnd(const BasicString& command, int& readIndex)
{
    if (!CommandReader::isCompleted(command, readIndex))
    {
        throw std::exception("Invalid command format!");
    }
}

void TrainSystem::loginAdmin(BasicString& username, BasicString& password)
{
    size_t count = admins.getSize();
    for (size_t i = 0; i < count; i++)
    {
        if (admins[i].getName() == username && admins[i].isPasswordCorrect(password))
        {
            loggedAdmin = &admins[i];
            std::cout << "Welcome back, " << username << '!' << std::endl;
            return;
        }
    }
    throw std::exception("Wrong username or password!");
}

void TrainSystem::addStation(BasicString& name)
{
    Station* searchResult = findStation(name);
    if (searchResult)
    {
        throw std::exception("Station with this name already exists!");
    }
    Station station(name);
    stations.push_back(station);
    std::cout << "Added station " << name << '!' << std::endl;
}

void TrainSystem::addTrain(BasicString& station, BasicString& destination, 
                           double distance, double speed, time_t departureTime)
{
    Station* departureStation = findStation(station);
    Station* arrivalStation = findStation(destination);
    if (departureStation == nullptr || arrivalStation == nullptr)
    {
        throw std::exception("Invalid station name!");
    }
    if (departureStation == arrivalStation)
    {
        throw std::exception("Departure and arrival stations cannot be the same!");
    }
    if (distance == 0 || speed == 0)
    {
        throw std::exception("Invalid distance or speed parameters!");
    }
    departureStation->addTrain(currentTrainId++, arrivalStation, distance, speed, departureTime);
    std::cout << "Train successfully added with ID: " << currentTrainId - 1 << std::endl;
}

void TrainSystem::removeTrain(unsigned id)
{
    size_t count = stations.getSize();
    for (size_t i = 0; i < count; i++)
    {
        if (stations[i].tryRemoveTrain(id))
        {
            std::cout << "Train with ID: " << id << " successfully removed." << std::endl;
            return;
        }
    }
    throw std::exception("Invalid train ID!");
}

void TrainSystem::checkForAdmin()
{
    if (!loggedAdmin)
    {
        throw std::exception("You need to be an admin to run this command!");
    }
}

void TrainSystem::start()
{
    try
    {
        loadAdmins();
    }
    catch (std::exception& e)
    {
        std::cout << e.what() << std::endl;
    }
    while (true)
    {
        try
        {
            BasicString command;
            std::cin >> command;
            if (command.equals("exit"))
            {
                break;
            }
            if (command.equals("print-stations"))
            {
                printStations();
                continue;
            }
            if (command.startsWith("print-schedule "))
            {
                int readIndex = 0;
                CommandReader::moveIndexByLength("print-schedule ", readIndex);
                BasicString name = CommandReader::readName(command, readIndex);
                checkForCommandEnd(command, readIndex);
                printSchedule(name);
                continue;
            }
            if (command.startsWith("print-schedule-destination"))
            {
                int readIndex = 0;
                CommandReader::moveIndexByLength("print-schedule-destination ", readIndex);
                BasicString stationName = CommandReader::readName(command, readIndex);
                readIndex++;
                BasicString destinationName = CommandReader::readName(command, readIndex);
                checkForCommandEnd(command, readIndex);
                printScheduleDestination(stationName, destinationName);
                continue;
            }
            if (command.startsWith("print-schedule-time"))
            {
                int readIndex = 0;
                CommandReader::moveIndexByLength("print-schedule-time ", readIndex);
                BasicString stationName = CommandReader::readName(command, readIndex);
                readIndex++;
                time_t time = CommandReader::readDateTime(command, readIndex);
                checkForCommandEnd(command, readIndex);
                printScheduleTime(stationName, time);
                continue;
            }
            if (command.startsWith("print-train"))
            {
                int readIndex = 0;
                CommandReader::moveIndexByLength("print-train ", readIndex);
                unsigned id = CommandReader::readUnsigned(command, readIndex);
                checkForCommandEnd(command, readIndex);
                printTrain(id);
                continue;
            }
            if (command.startsWith("print-wagon"))
            {
                int readIndex = 0;
                CommandReader::moveIndexByLength("print-wagon ", readIndex);
                unsigned trainId = CommandReader::readUnsigned(command, readIndex);
                readIndex++;
                unsigned wagonId = CommandReader::readUnsigned(command, readIndex);
                checkForCommandEnd(command, readIndex);
                printWagon(trainId, wagonId);
                continue;
            }
            if (command.startsWith("buy-ticket "))
            {
                int readIndex = 0;
                CommandReader::moveIndexByLength("buy-ticket ", readIndex);
                unsigned trainId = CommandReader::readUnsigned(command, readIndex);
                readIndex++;
                unsigned wagonId = CommandReader::readUnsigned(command, readIndex);
                readIndex++;
                unsigned seatId = CommandReader::readUnsigned(command, readIndex);
                readIndex++;
                BasicString ticketFile = CommandReader::readWord(command, readIndex);
                buyTicket(command, readIndex, trainId, wagonId, seatId, ticketFile);
                continue;
            }
            if (command.startsWith("login"))
            {
                if (loggedAdmin)
                {
                    throw std::exception("An admin is already logged. Please logout first.");
                }
                int readIndex = 0;
                CommandReader::moveIndexByLength("login ", readIndex);
                BasicString username = CommandReader::readName(command, readIndex);
                readIndex++;
                BasicString password = CommandReader::readPassword(command, readIndex);
                checkForCommandEnd(command, readIndex);
                loginAdmin(username, password);
                continue;
            }
            if (command.equals("logout"))
            {
                if (!loggedAdmin)
                {
                    throw std::exception("No user is currently logged.");
                }
                loggedAdmin = nullptr;
                continue;
            }
            if (command.startsWith("add-station"))
            {
                checkForAdmin();
                int readIndex = 0;
                CommandReader::moveIndexByLength("add-station ", readIndex);
                BasicString stationName = CommandReader::readName(command, readIndex);
                checkForCommandEnd(command, readIndex);
                addStation(stationName);
                continue;
            }
            if (command.startsWith("add-train"))
            {
                checkForAdmin();
                int readIndex = 0;
                CommandReader::moveIndexByLength("add-train ", readIndex);
                BasicString station = CommandReader::readName(command, readIndex);
                readIndex++;
                BasicString destination = CommandReader::readName(command, readIndex);
                readIndex++;
                double distance = CommandReader::readDouble(command, readIndex);
                readIndex++;
                double speed = CommandReader::readDouble(command, readIndex);
                readIndex++;
                time_t departureTime = CommandReader::readDateTime(command, readIndex);
                checkForCommandEnd(command, readIndex);
                addTrain(station, destination, distance, speed, departureTime);
                continue;
            }
            if (command.startsWith("remove-train"))
            {
                checkForAdmin();
                int readIndex = 0;
                CommandReader::moveIndexByLength("remove-train ", readIndex);
                unsigned id = CommandReader::readUnsigned(command, readIndex);
                checkForCommandEnd(command, readIndex);
                removeTrain(id);
                continue;
            }
            if (command.startsWith("add-wagon"))
            {
                checkForAdmin();
                int readIndex = 0;
                CommandReader::moveIndexByLength("add-wagon ", readIndex);
                unsigned trainId = CommandReader::readUnsigned(command, readIndex);
                readIndex++;
                BasicString wagonType = CommandReader::readWord(command, readIndex);
                readIndex++;
                unsigned basePrice = CommandReader::readUnsigned(command, readIndex);
                readIndex++;
                addWagon(trainId, wagonType, command, readIndex, basePrice);
                continue;
            }
            if (command.startsWith("remove-wagon"))
            {
                checkForAdmin();
                int readIndex = 0;
                CommandReader::moveIndexByLength("remove-wagon ", readIndex);
                unsigned trainId = CommandReader::readUnsigned(command, readIndex);
                readIndex++;
                unsigned wagonId = CommandReader::readUnsigned(command, readIndex);
                checkForCommandEnd(command, readIndex);
                removeWagon(trainId, wagonId);
                continue;
            }
            if (command.startsWith("create-discount-card"))
            {
                checkForAdmin();
                int readIndex = 0;
                CommandReader::moveIndexByLength("create-discount-card ", readIndex);
                BasicString cardType = CommandReader::readWord(command, readIndex);
                readIndex++;
                BasicString username = CommandReader::readName(command, readIndex);
                readIndex++;
                BasicString cardFile = CommandReader::readWord(command, readIndex);
                if (cardType.equals("age-card"))
                {
                    readIndex++;
                    unsigned age = CommandReader::readUnsigned(command, readIndex);
                    checkForCommandEnd(command, readIndex);
                    CardManager::instance()->createAgeCard(username, age, cardFile);
                }
                else if (cardType.equals("route-card"))
                {
                    readIndex++;
                    BasicString route = CommandReader::readName(command, readIndex);
                    Station* station = findStation(route);
                    if (!station)
                    {
                        throw std::exception("Invalid route!");
                    }
                    checkForCommandEnd(command, readIndex);
                    CardManager::instance()->createRouteCard(username, route, cardFile);
                }
                else if (cardType.equals("distance-card"))
                {
                    readIndex++;
                    unsigned distance = CommandReader::readUnsigned(command, readIndex);
                    checkForCommandEnd(command, readIndex);
                    CardManager::instance()->createDistanceCard(username, distance, cardFile);
                }
                else
                {
                    throw std::exception("Invalid card type!");
                }
                continue;
            }
            throw std::exception("Invalid command!");
        }
        catch(std::exception& e)
        {
            std::cout << e.what() << std::endl;
        }
    }
}

void TrainSystem::buyTicket(BasicString& command, int& readIndex, unsigned int trainId, unsigned int wagonId, unsigned int seatId, BasicString& ticketFile)
{
    Train* train = findTrain(trainId);
    if (!train)
    {
        throw std::exception("Invalid train ID!");
    }
    Wagon* wagon = train->findWagon(wagonId);
    if (!wagon)
    {
        throw std::exception("Invalid wagon ID!");
    }
    double price = 0;
    BasicString wagonType = wagon->getType();
    BasicString destination = train->getArrival().getStation()->getName();
    if (wagonType.equals("First Class"))
    {
        readIndex++;
        bool foodIncluded = CommandReader::readBool(command, readIndex);
        checkForCommandEnd(command, readIndex);
        wagon->reserveSeat(seatId);
        PassengerInfo info(destination, foodIncluded, 0, 0);
        price = wagon->getPrice(info);
    }
    else if (wagonType.equals("Second Class"))
    {
        readIndex++;
        unsigned baggageKg = CommandReader::readUnsigned(command, readIndex);
        checkForCommandEnd(command, readIndex);
        wagon->reserveSeat(seatId);
        PassengerInfo info(destination, false, baggageKg, 0);
        price = wagon->getPrice(info);
    }
    else if (wagonType.equals("Sleep Wagon"))
    {
        checkForCommandEnd(command, readIndex);
        wagon->reserveSeat(seatId);
        PassengerInfo info(destination, false, 0, train->getDistance());
        price = wagon->getPrice(info);
    }
    else
    {
        throw std::exception("Invalid wagon type!");
    }
    Ticket ticket(train, wagon, seatId, 0, price);
    ticket.writeToFile(ticketFile);
    std::cout << "Ticket successfully bought for Train ID: " << trainId << std::endl;
    std::cout << "Ticket price: " << price << " lv." << std::endl;
    std::cout << "Ticket saved to file: " << ticketFile << std::endl;
}

void TrainSystem::removeWagon(unsigned trainId, unsigned wagonId)
{
    Train* train = findTrain(trainId);
    if (!train)
    {
        throw std::exception("Invalid train ID!");
    }
    train->removeWagon(wagonId);
}

void TrainSystem::addWagon(unsigned trainId, BasicString& wagonType, BasicString& command, int& readIndex, unsigned basePrice)
{
    Train* train = findTrain(trainId);
    if (!train)
    {
        throw std::exception("Invalid train ID!");
    }
    if (wagonType.equals("first-class"))
    {
        double comfortFactor = CommandReader::readDouble(command, readIndex);
        if (comfortFactor > 1)
        {
            throw std::exception("Invalid comfort factor!");
        }
        checkForCommandEnd(command, readIndex);
        train->addFirstClassWagon(basePrice, comfortFactor);
        return;
    }
    if (wagonType.equals("second-class"))
    {
        unsigned pricePerKg = CommandReader::readUnsigned(command, readIndex);
        checkForCommandEnd(command, readIndex);
        train->addSecondClassWagon(basePrice, pricePerKg);
        return;
    }
    if (wagonType.equals("sleep-wagon"))
    {
        unsigned pricePer100km = CommandReader::readUnsigned(command, readIndex);
        checkForCommandEnd(command, readIndex);
        train->addSleepWagon(basePrice, pricePer100km);
        return;
    }
    throw std::exception("Invalid wagon type!");
}

void TrainSystem::printStations() const
{
    size_t count = stations.getSize();
    for (size_t i = 0; i < count; i++)
    {
        std::cout << stations[i].getName() << std::endl;
    }
}

void TrainSystem::printSchedule(const BasicString& name) const
{
    size_t stationCount = stations.getSize();
    for (size_t i = 0; i < stationCount; i++)
    {
        if (stations[i].getName() == name)
        {
            stations[i].printSchedule();
            return;
        }
    }
    throw std::exception("Invalid train station!");
}

void TrainSystem::printScheduleDestination(const BasicString& stationName, const BasicString& destinationName) const
{
    const Station* station = nullptr;
    const Station* destination = nullptr;
    size_t stationCount = stations.getSize();
    for (size_t i = 0; i < stationCount; i++)
    {
        if (stations[i].getName() == stationName)
        {
            station = &stations[i];
        }
        if (stations[i].getName() == destinationName)
        {
            destination = &stations[i];
        }
    }
    if (!station)
    {
        throw std::exception("Invalid train station!");
    }
    if (!destination)
    {
        throw std::exception("Invalid destination!");
    }
    if (station == destination)
    {
        throw std::exception("Start station and destination cannot be the same!");
    }
    station->printScheduleDestination(destination);
}

void TrainSystem::printScheduleTime(const BasicString& stationName, time_t time) const
{
    size_t stationCount = stations.getSize();
    for (size_t i = 0; i < stationCount; i++)
    {
        if (stations[i].getName() == stationName)
        {
            stations[i].printScheduleTime(time);
            return;
        }
    }
    throw std::exception("Invalid train station!");
}

void TrainSystem::printTrain(unsigned id) const
{
    size_t stationCount = stations.getSize();
    for (size_t i = 0; i < stationCount; i++)
    {
        const Train* train = stations[i].findTrain(id);
        if (train)
        {
            train->print();
            return;
        }
    }
    throw std::exception("Invalid train ID!");
}

void TrainSystem::printWagon(unsigned trainId, unsigned wagonId) const
{
    const Train* train = findTrain(trainId);
    if (!train)
    {
        throw std::exception("Invalid train ID!");
    }
    const Wagon* wagon = train->findWagon(wagonId);
    if (!wagon)
    {
        throw std::exception("Invalid wagon ID!");
    }
    wagon->print();
}

unsigned TrainSystem::getMaxTrainId() const
{
    unsigned max = 0;
    size_t stationCount = stations.getSize();
    for (size_t i = 0; i < stationCount; i++)
    {
        unsigned current = stations[i].getMaxTrainId();
        if (current > max)
        {
            max = current;
        }
    }
    return max;
}

Station* TrainSystem::findStation(BasicString& name)
{
    size_t count = stations.getSize();
    for (size_t i = 0; i < count; i++)
    {
        if (stations[i].getName() == name)
        {
            return &stations[i];
        }
    }
    return nullptr;
}

Train* TrainSystem::findTrain(unsigned id)
{
    size_t count = stations.getSize();
    for (size_t i = 0; i < count; i++)
    {
        Train* train = stations[i].findTrain(id);
        if (train)
        {
            return train;
        }
    }
    return nullptr;
}

const Train* TrainSystem::findTrain(unsigned id) const
{
    size_t count = stations.getSize();
    for (size_t i = 0; i < count; i++)
    {
        const Train* train = stations[i].findTrain(id);
        if (train)
        {
            return train;
        }
    }
    return nullptr;
}

TrainSystem* TrainSystem::instance()
{
    if (system)
    {
        return system;
    }
    system = new TrainSystem();
    return system;
}
