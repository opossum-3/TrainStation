#include "TrainSystem.h"

TrainSystem* TrainSystem::system;

TrainSystem::TrainSystem()
{

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
