#include "TrainSystem.h"
#include "CommandReader.h"
#include <fstream>
#include <iostream>

TrainSystem* TrainSystem::system;

TrainSystem::TrainSystem()
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

void TrainSystem::checkForCommandEnd(BasicString command, int& readIndex)
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
    size_t count = stations.getSize();
    for (size_t i = 0; i < count; i++)
    {
        if (stations[i].getName() == name)
        {
            throw std::exception("Station with this name already exists!");
        }
    }
    Station station(name);
    stations.push_back(station);
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
    loggedAdmin = nullptr;
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

TrainSystem* TrainSystem::instance()
{
    if (system)
    {
        return system;
    }
    system = new TrainSystem();
    return system;
}
