#include "TrainSystem.h"
#include "CommandReader.h"
#include "Wagon.h"
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
            if (command.startsWith("print-schedule"))
            {
                int readIndex = 0;
                CommandReader::moveIndexByLength("print-schedule ", readIndex);
                BasicString name = CommandReader::readName(command, readIndex);
                checkForCommandEnd(command, readIndex);
                printSchedule(name);
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
                Train* train = findTrain(trainId);
                if (!train)
                {
                    throw std::exception("Invalid train ID!");
                }
                if (wagonType.equals("first-class"))
                {
                    double comfortFactor = CommandReader::readDouble(command, readIndex);
                    checkForCommandEnd(command, readIndex);
                    train->addFirstClassWagon(basePrice, comfortFactor);
                    continue;
                }
                if (wagonType.equals("second-class"))
                {
                    unsigned pricePerKg = CommandReader::readUnsigned(command, readIndex);
                    checkForCommandEnd(command, readIndex);
                    train->addSecondClassWagon(basePrice, pricePerKg);
                    continue;
                }
                if (wagonType.equals("sleep-wagon"))
                {
                    unsigned pricePer100km = CommandReader::readUnsigned(command, readIndex);
                    checkForCommandEnd(command, readIndex);
                    train->addSleepWagon(basePrice, pricePer100km);
                    continue;
                }
                throw std::exception("Invalid wagon type!");
            }
            throw std::exception("Invalid command!");
        }
        catch(std::exception& e)
        {
            std::cout << e.what() << std::endl;
        }
    }
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

TrainSystem* TrainSystem::instance()
{
    if (system)
    {
        return system;
    }
    system = new TrainSystem();
    return system;
}
