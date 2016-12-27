#include "spawnprojectile.hpp"
#include "../entity/entityutil.hpp"
#include "../orientationutil.hpp"
#include "resources/textureutil.hpp"
#include "resources/animationutil.hpp"

int32_t spawnBall(glm::vec2 position, glm::vec2 direction, GameData& data)
{
    Orientation orientation = toOrientation(direction);

    return addEntity(Entity{{position}, orientation,
    {
        direction,
    },
    Hitbox
    {
        AABB
        {
            {1, 1},
            {6, 6}
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
            *findTexture("energy_ball"_hash, data),
            {8*4, 8*4},
            {.animatedSprite=Entity::EntitySprite::AnimatedSprite
            {
                *findAnimation("energy_ball"_hash, data),
            }},
        }
    },
    Entity::EntityState
    {
        "energy_ball"_hash,
        "travel"_hash,
    }}, data);
}
