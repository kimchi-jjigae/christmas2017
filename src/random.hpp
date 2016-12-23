#pragma once
#include <cstdint>
#include "direction.hpp"

struct GameData;

int32_t randomRange(int32_t low, int32_t high, GameData& data);
Direction randomDirection(GameData& data);
