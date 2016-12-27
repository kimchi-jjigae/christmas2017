#pragma once
#include <cstdint>
#include "orientation.hpp"

struct GameData;

int32_t randomRange(int32_t low, int32_t high, GameData& data);
Orientation randomDirection(GameData& data);
