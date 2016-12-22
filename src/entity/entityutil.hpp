#pragma once
#include <cstdint>
#include "entity.hpp"

struct GameData;

int32_t addEntity(Entity entity, GameData& data);
void setEntitySpritesDirection(int32_t entityId, Direction direction, GameData& data);
