#include "spawnplayer.hpp"
#include "../entity/entityutil.hpp"
#include "resources/textureutil.hpp"
#include "resources/animationutil.hpp"
#include <gamedata.hpp>

int32_t spawnPlayer(GameData& data)
{
    int32_t player = addEntity(Entity{{{30000.0f, 30000.0f}}, {spr::Orientation::Down},
    {
        {0.0f, 1.0f},
    },
    spr::Hitbox
    {
        spr::AABB
        {
            {2 * 4, 2 * 4},
            {8 * 4, 10 * 4}
        }
    },
    spr::EntityCollider
    {
        spr::CollisionType::Trigger,
        spr::CollisionExecutors{},
    },
    Health
    {
        100,
    },
    {
        Entity::EntitySprite
        {
            spr::Sprite::FourDirectionalSprite,
            {0.0f, 0.0f},
            *findTexture("wizard"_hash, data.spr),
            {12*4, 14*4},
            {.fourDirectionalSprite=Entity::EntitySprite::FourDirectionalSprite
            {
                *findFourDirectionalAnimationGroup("wizard_walk"_hash, data.spr),
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
