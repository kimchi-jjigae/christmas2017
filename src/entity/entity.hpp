#pragma once
#include <spr/hash/stringhash.hpp>
#include <spr/data/sprite.hpp>
#include <spr/data/position.hpp>
#include <spr/data/entityorientation.hpp>
#include <spr/data/hitbox.hpp>
#include <spr/data/entitycollider.hpp>
#include <data/health.hpp>

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

        spr::Sprite::Type type;
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
        spr::StringHash stateSet;
        spr::StringHash state;
    };

    spr::Position position;
    spr::EntityOrientation orientation;
    th::Optional<glm::vec2> entityDirection;
    th::Optional<spr::Hitbox> hitbox;
    th::Optional<spr::EntityCollider> entityCollider;
    th::Optional<Health> health;
    std::vector<EntitySprite> sprites;
    th::Optional<EntityState> entityState;
};
