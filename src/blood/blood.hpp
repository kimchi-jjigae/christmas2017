#pragma once
#include <gamedata.hpp>
#include <dpx/tableid.hpp>
#include <spr/glm.hpp>

void spawnBloodSplash(const glm::vec3& childSpawnPosition, const float speed, const int32_t health, const ChildType type, GameData& data);
dpx::TableId spawnBloodParticle(const glm::vec3& position, const glm::vec2 velocity, GameData& data);
