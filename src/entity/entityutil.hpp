#pragma once
#include <cstdint>
#include "entityproperties.hpp"

struct GameData;

int32_t addEntity(EntityProperties properties, GameData& data);
void removeEntity(int32_t entityId, GameData& data);
void removeEntityData(int32_t entityId, GameData& data);
void clearAllCurrentEntities(GameData& data);
bool withinSpatialBounds(glm::vec2 position, GameData& data);
bool withinSpatialBoundsX(float x, GameData& data);
bool withinSpatialBoundsY(float y, GameData& data);
