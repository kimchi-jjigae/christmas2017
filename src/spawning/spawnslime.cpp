#include "spawnprojectile.hpp"
#include "../entity/entityutil.hpp"
#include "resources/textureutil.hpp"
#include "resources/animationutil.hpp"

int32_t spawnSlime(glm::vec2 position, GameData& data)
{
    return addEntity(Entity{{position}, Orientation::Down,
    {
        glm::vec2(0.0f, 1.0f),
    },
    Hitbox
    {
        AABB
        {
            {1, 1},
            {8, 8}
        }
    },
    EntityCollider
    {
        CollisionType::Trigger,
    },
    {
        Entity::EntitySprite
        {
            Sprite::AnimatedSprite,
            {0.0f, 0.0f},
            *findTexture("slime"_hash, data),
            {10*4, 10*4},
            {.animatedSprite=Entity::EntitySprite::AnimatedSprite
            {
                *findAnimation("slime"_hash, data),
            }},
        }
    },
    Entity::EntityState
    {
        "slime"_hash,
        "engage"_hash,
    }}, data);
}
