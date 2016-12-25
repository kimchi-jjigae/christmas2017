#pragma once
#include <glm/glm.hpp>

#include <glm/gtx/io.hpp>
#include <glm/gtc/random.hpp>
#include <glm/gtc/noise.hpp>
#include <glm/gtx/string_cast.hpp>
#include <fea/rendering/glmhash.hpp>

template<typename Vec2Type>
std::string toString(const glm::tvec2<Vec2Type>& vec2)
{
    return std::to_string(vec2.x) + " " + std::to_string(vec2.y);
}
