#include "spawnplayer.hpp"
#include "../entity/entityutil.hpp"
#include "resources/textureutil.hpp"
#include "resources/animationutil.hpp"

int32_t spawnPlayer(GameData& data)
{
    int32_t player = addEntity(Entity{{{30000.0f, 30000.0f}}, Orientation::Down,
    {
        {0.0f, 1.0f},
    },
    Hitbox
    {
        AABB
        {
            {2 * 4, 2 * 4},
            {8 * 4, 10 * 4}
        }
    },
    EntityCollider
    {
        CollisionType::Trigger,
        CollisionExecutors{},
    },
    {
        Entity::EntitySprite
        {
            Sprite::FourDirectionalSprite,
            {0.0f, 0.0f},
            *findTexture("wizard"_hash, data),
            {12*4, 14*4},
            {.fourDirectionalSprite=Entity::EntitySprite::FourDirectionalSprite
            {
                *findFourDirectionalAnimationGroup("wizard_walk"_hash, data),
            }},
        }
    },
    Entity::EntityState
    {
        "player"_hash,
        "idle"_hash,
    }}, data);

    data.camera.cameraEntity = player;

    return player;
}
