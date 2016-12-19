#pragma once
#include <data.hpp>

struct Entity
{
    struct EntitySprite
    {
        glm::vec2 offset;
        int32_t texture;
        glm::vec2 size;
    };

    Position position;
    std::vector<EntitySprite> sprites;
};
