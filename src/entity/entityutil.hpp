#pragma once
#include <cstdint>
#include "entity.hpp"

struct GameData;

int32_t addEntity(Entity entity, GameData& data);
void setEntityFourDirectionalAnimationGroup(int32_t entityId, int32_t animationGroup, GameData& data);
