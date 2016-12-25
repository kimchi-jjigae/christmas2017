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
            int32_t animationGroup;
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

    struct EntityState
    {
        StringHash stateSet;
        StringHash state;
    };

    Position position;
    Orientation orientation;
    th::Optional<Hitbox> hitbox;
    th::Optional<EntityCollider> entityCollider;
    std::vector<EntitySprite> sprites;
    th::Optional<EntityState> entityState;
};
