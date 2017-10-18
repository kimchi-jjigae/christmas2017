#pragma once
#include <gamedata.hpp>
#include <dpx/tableid.hpp>
#include <spr/glm.hpp>

void spawnBloodSplash(const glm::vec3& childSpawnPosition, float landingYPos, const float speed, const int32_t amount, GameData& data);
dpx::TableId spawnBloodParticle(const glm::vec3& position, const glm::vec2 velocity, float landingYPos, GameData& data);
