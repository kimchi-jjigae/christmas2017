#include "spawnprojectile.hpp"
#include "../entity/entityutil.hpp"
#include <spr/orientation/orientationutil.hpp>
#include "resources/textureutil.hpp"
#include "resources/animationutil.hpp"
#include <gamedata.hpp>

int32_t spawnBall(glm::vec2 position, glm::vec2 direction, GameData& data)
{
    spr::Orientation orientation = spr::toOrientation(direction);

    return addEntity(Entity{{position}, {orientation},
    {
        direction,
    },
    spr::Hitbox
    {
        spr::AABB
        {
            {1 * 4, 1 * 4},
            {6 * 4, 6 * 4}
        }
    },
    spr::EntityCollider
    {
        spr::CollisionType::Trigger,
        spr::CollisionExecutors
        {
            {
                "Damage entities",
                [&] (const spr::CollisionContext& context)
                {
                    if(context.collidedWithId != data.playerId)
                    {
                        int32_t targetId = context.collidedWithId;
                        auto health = findId(targetId, *data.game.tHealth);

                        if(health)
                        {
                            health->amount -= 8;
                            removeEntity(context.entityId, data);
                        }
                    }
                },
            }
        },
    },
    {},
    {
        Entity::EntitySprite
        {
            spr::Sprite::AnimatedSprite,
            {0.0f, 0.0f},
            *findTexture("energy_ball"_hash, data.spr),
            {8*4, 8*4},
            {.animatedSprite=Entity::EntitySprite::AnimatedSprite
            {
                *findAnimation("energy_ball"_hash, data.spr),
            }},
        }
    },
    Entity::EntityState
    {
        "energy_ball"_hash,
        "travel"_hash,
    }}, data);
}
