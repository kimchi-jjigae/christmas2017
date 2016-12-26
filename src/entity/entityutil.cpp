#include "entityutil.hpp"
#include "../entitystates/stateutil.hpp"
#include <data.hpp>

int32_t addEntity(Entity entity, GameData& data)
{
    glm::vec2 position = entity.position.coordinate;
    int32_t newId = insert(std::move(entity.position), data.tPosition).id;
    insert(newId, std::move(entity.orientation), data.tOrientation);

    if(entity.hitbox)
        insert(newId, std::move(*entity.hitbox), data.tHitbox);
    if(entity.entityCollider)
        insert(newId, std::move(*entity.entityCollider), data.tEntityCollider);

    for(auto sprite : entity.sprites)
    {
        int32_t spriteId = 0;

        Sprite newSprite
        {
            {},
            position + sprite.offset,
            sprite.size,
            sprite.texture,
        };

        if(sprite.type == Sprite::AnimatedSprite)
        {
            spriteId = insertAnimatedSprite(std::move(newSprite),
            AnimatedSprite
            {
                sprite.animatedSprite.animation,
                0,
            }, data);
        }
        else if(sprite.type == Sprite::FourDirectionalSprite)
        {
            spriteId = insertFourDirectionalSprite(std::move(newSprite),
            FourDirectionalSprite
            {
                Direction::Up,
                sprite.fourDirectionalSprite.animationGroup,
                0,
            }, data);
        }

        insert(EntitySpriteInstance
        {
            newId,
            spriteId,
            sprite.offset,
        }, data.tEntitySpriteInstance);
    }

    if(entity.entityState)
    {
        insert(EntityStateMachine
        {
            newId,
            entity.entityState->stateSet,
            getEntityState(entity.entityState->stateSet, entity.entityState->state, data).id,
            {},
        }, data.tEntityStateMachine);
    }

    return newId;
}

void removeEntity(int32_t entityId, GameData& data)
{
    insert(entityId, data.entitiesToRemove);
}

void removeEntityData(int32_t entityId, GameData& data)
{
    erase(entityId, data.tPosition);
    erase(entityId, data.tOrientation);
    erase(entityId, data.tHitbox);
    erase(entityId, data.tEntityCollider);
    erase(entityId, data.tEntityStateMachine);

    eraseIf([&](int32_t entitySpriteId, const EntitySpriteInstance& entitySpriteInstance)
    {
        if(entitySpriteInstance.entityId == entityId)
        {
            erase(entitySpriteInstance.spriteId, data.tSprite);
            return true;
        }
        else
        {
            return false;
        }
    }, data.tEntitySpriteInstance);
}

void setEntityFourDirectionalAnimationGroup(int32_t entityId, int32_t animationGroup, GameData& data)
{
    auto found = findOne([&](int32_t id, const EntitySpriteInstance& objSpriteInstance)
    {
        return objSpriteInstance.entityId == entityId;
    }, data.tEntitySpriteInstance);

    TH_ASSERT(found, "trying to set four directional animation group on entity " << entityId << " which lacks an objSpriteInstance");
    TH_ASSERT(has(found->data.spriteId, data.tFourDirectionalSprite), "trying to set four directional animation group on entity " << entityId << " which doesn't have a FourDirectionalSprite");
    FourDirectionalSprite& sprite = get(found->data.spriteId, data.tFourDirectionalSprite);

    sprite.animationGroup = animationGroup;
}
