#pragma once
#include "orientation.hpp"
#include <glm.hpp>

glm::vec2 toDirection(Orientation orientation);
Orientation toOrientation(glm::vec2 vec);
bool vec2ContainsOrientation(glm::vec2 vec, Orientation orientation);
