#pragma once
#include <spr/glm.hpp>

namespace spr
{
template<typename Vec2Type>
std::string toString(const glm::tvec2<Vec2Type>& vec2)
{
    return std::to_string(vec2.x) + " " + std::to_string(vec2.y);
}
}
