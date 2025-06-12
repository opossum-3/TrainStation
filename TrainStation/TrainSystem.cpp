#include "TrainSystem.h"
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
