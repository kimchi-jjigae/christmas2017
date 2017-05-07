#pragma once
#include <spr/glm.hpp>
#include <thero/optional.hpp>

struct SystemInput
{
    bool quit;
    th::Optional<glm::ivec2> resized;
};

enum class MouseButton { Left, Right, Middle };

struct MouseClick
{
    glm::ivec2 position;
    MouseButton button;
};

struct MouseRelease
{
    glm::ivec2 position;
    MouseButton button;
};
