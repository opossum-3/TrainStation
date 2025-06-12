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
        std::cout << e.what();
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
