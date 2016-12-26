#include <data.hpp>
#include "playerstates.hpp"
#include "energyballstates.hpp"
#include "slimestates.hpp"

void registerEntityStates(GameData& data)
{
    registerPlayerStates(data);
    registerEnergyBallStates(data);
    registerSlimeStates(data);
}
