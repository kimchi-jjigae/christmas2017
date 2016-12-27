#pragma once
#include <cstdint>
#include "../orientation.hpp"
#include <glm.hpp>

struct GameData;

int32_t spawnBall(glm::vec2 position, glm::vec2 direction, GameData& data);