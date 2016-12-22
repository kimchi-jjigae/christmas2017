#include "entityutil.hpp"
#include "../entitystates/stateutil.hpp"
#include <data.hpp>

int32_t addEntity(Entity entity, GameData& data)
{
    glm::vec2 position = entity.position.coordinate;
    int32_t newId = insert(std::move(entity.position), data.tPosition).id;

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
                sprite.fourDirectionalSprite.upAnimation,
                sprite.fourDirectionalSprite.downAnimation,
                sprite.fourDirectionalSprite.leftAnimation,
                sprite.fourDirectionalSprite.rightAnimation,
                0,
            }, data);
        }

        insert(ObjectSpriteInstance
        {
            newId,
            spriteId,
            sprite.offset,
        }, data.tObjectSpriteInstance);
    }

    if(entity.entityState)
    {
        insert(EntityStateMachine
        {
            0,
            entity.entityState->stateSet,
            getEntityState(entity.entityState->stateSet, entity.entityState->state, data).id,
            {},
        }, data.tEntityStateMachine);
    }

    return newId;
}

void setEntitySpritesDirection(int32_t entityId, Direction direction, GameData& data)
{
    auto objectSpriteInstances = findAll([&](int32_t id, const ObjectSpriteInstance& obj)
    {
        return obj.objectId == entityId;
    }, data.tObjectSpriteInstance);

    for(auto& objectSpriteInstance : objectSpriteInstances)
    {
        auto& sprite = get(objectSpriteInstance.data.spriteId, data.tFourDirectionalSprite);
        sprite.currentDirection = direction;
    }
}
