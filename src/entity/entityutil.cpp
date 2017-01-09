#include "entityutil.hpp"
#include <spr/entitystates/stateutil.hpp>
#include <gamedata.hpp>
#include <spr/data/entitydirection.hpp>
#include <spr/data/entityspriteinstance.hpp>
#include <spr/data/entitystatemachine.hpp>
#include <spr/data/animatedsprite.hpp>
#include <spr/data/fourdirectionalsprite.hpp>

int32_t addEntity(Entity entity, GameData& data)
{
    glm::vec2 position = entity.position.coordinate;
    int32_t newId = insert(std::move(entity.position), *data.spr.tPosition).id;
    insert(newId, {std::move(entity.orientation)}, *data.spr.tEntityOrientation);

    if(entity.entityDirection)
        insert(newId, {std::move(*entity.entityDirection)}, *data.spr.tEntityDirection);
    if(entity.hitbox)
        insert(newId, std::move(*entity.hitbox), *data.spr.tHitbox);
    if(entity.entityCollider)
        insert(newId, std::move(*entity.entityCollider), *data.spr.tEntityCollider);
    if(entity.health)
        insert(newId, std::move(*entity.health), *data.game.tHealth);

    for(auto sprite : entity.sprites)
    {
        int32_t spriteId = 0;

        spr::Sprite newSprite
        {
            {},
            position + sprite.offset,
            sprite.size,
            sprite.texture,
        };

        if(sprite.type == spr::Sprite::AnimatedSprite)
        {
            spriteId = spr::insertSprite(std::move(newSprite),
            spr::AnimatedSprite
            {
                sprite.animatedSprite.animation,
                0,
            }, data.spr);
        }
        else if(sprite.type == spr::Sprite::FourDirectionalSprite)
        {
            spriteId = spr::insertSprite(std::move(newSprite),
            spr::FourDirectionalSprite
            {
                spr::Orientation::Up,
                sprite.fourDirectionalSprite.animationGroup,
                0,
            }, data.spr);
        }

        insert(spr::EntitySpriteInstance
        {
            newId,
            spriteId,
            sprite.offset,
        }, *data.spr.tEntitySpriteInstance);
    }

    if(entity.entityState)
    {
        insert(spr::EntityStateMachine
        {
            newId,
            entity.entityState->stateSet,
            getEntityState(entity.entityState->stateSet, entity.entityState->state, data.spr).id,
            {},
        }, *data.spr.tEntityStateMachine);
    }

    return newId;
}

void removeEntity(int32_t entityId, GameData& data)
{
    if(!has(entityId, data.entitiesToRemove))
        insert(entityId, data.entitiesToRemove);
}

void removeEntityData(int32_t entityId, GameData& data)
{
    erase(entityId, *data.spr.tPosition);
    erase(entityId, *data.spr.tEntityOrientation);
    erase(entityId, *data.spr.tEntityDirection);
    erase(entityId, *data.spr.tHitbox);
    erase(entityId, *data.spr.tEntityCollider);
    erase(entityId, *data.game.tHealth);
    erase(entityId, *data.spr.tEntityStateMachine);

    eraseIf([&](int32_t entitySpriteId, const spr::EntitySpriteInstance& entitySpriteInstance)
    {
        if(entitySpriteInstance.entityId == entityId)
        {
            spr::eraseSprite(entitySpriteInstance.spriteId, data.spr);
            return true;
        }
        else
        {
            return false;
        }
    }, *data.spr.tEntitySpriteInstance);
}
