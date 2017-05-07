#include "gamedata.hpp"
#include <data/alltypes.hpp>
#include <spr/data/alltypes.hpp>

GameData::GameData()
{
    spr::instantiateTables(spr);
    instantiateGameTables(game);
}

GameData::~GameData()
{
}
