#pragma once
#include <data.hpp>

struct Entity
{
    struct EntitySprite
    {
        struct AnimatedSprite
        {
            int32_t animation;
        };
        struct FourDirectionalSprite
        {
            int32_t upAnimation;
            int32_t downAnimation;
            int32_t leftAnimation;
            int32_t rightAnimation;
        };

        Sprite::Type type;
        glm::vec2 offset;
        int32_t texture;
        glm::vec2 size;
        union
        {
            AnimatedSprite animatedSprite;
            FourDirectionalSprite fourDirectionalSprite;
        };
    };

    Position position;
    std::vector<EntitySprite> sprites;
};
