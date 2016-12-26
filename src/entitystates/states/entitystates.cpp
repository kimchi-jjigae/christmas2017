#include <data.hpp>
#include "playerstates.hpp"
#include "energyballstates.hpp"

void registerEntityStates(GameData& data)
{
    registerPlayerStates(data);
    registerEnergyBallStates(data);
}
