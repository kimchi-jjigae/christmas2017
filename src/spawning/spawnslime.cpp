#include "spawnprojectile.hpp"
#include "../entity/entityutil.hpp"
#include "resources/textureutil.hpp"
#include "resources/animationutil.hpp"
#include <gamedata.hpp>

int32_t spawnSlime(glm::vec2 position, GameData& data)
{
    return addEntity(Entity{{position}, spr::Orientation::Down,
    {
        glm::vec2(0.0f, 1.0f),
    },
    spr::Hitbox
    {
        spr::AABB
        {
            {1 * 4, 1 * 4},
            {8 * 4, 8 * 4}
        }
    },
    spr::EntityCollider
    {
        spr::CollisionType::Trigger,
        spr::CollisionExecutors
        {
            {
                "hej",
                [&] (const spr::CollisionContext& context)
                {
                },
            }
        },
    },
    Health
    {
        40,
    },
    {
        Entity::EntitySprite
        {
            spr::Sprite::AnimatedSprite,
            {0.0f, 0.0f},
            *findTexture("slime"_hash, data.spr),
            {10*4, 10*4},
            {.animatedSprite=Entity::EntitySprite::AnimatedSprite
            {
                *findAnimation("slime"_hash, data.spr),
            }},
        }
    },
    Entity::EntityState
    {
        "slime"_hash,
        "engage"_hash,
    }}, data);
}
