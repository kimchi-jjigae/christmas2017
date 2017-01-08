#include "playerstates.hpp"
#include "energyballstates.hpp"
#include "slimestates.hpp"

struct GameData;

void registerEntityStates(GameData& data)
{
    registerPlayerStates(data);
    registerEnergyBallStates(data);
    registerSlimeStates(data);
}
