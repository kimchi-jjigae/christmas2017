#include "entitylogic.hpp"

EntityLogic::EntityLogic(GameData& data):
    mData(data)
{
}

void EntityLogic::update()
{
    forEach([&](int32_t id, ObjectSpriteInstance& objectSprite)
    {
        int32_t spriteId = objectSprite.spriteId;
        Sprite& sprite = get(spriteId, mData.tSprite);       
        const Position& position = get(objectSprite.objectId, mData.tPosition);       

        sprite.position = position.coordinate + objectSprite.offset;

        if(sprite.type == Sprite::AnimatedSprite)
        {
            AnimatedSprite& animatedSprite = get(spriteId, mData.tAnimatedSprite);
            ++animatedSprite.animationClock;
        }
        else if(sprite.type == Sprite::FourDirectionalSprite)
        {
            FourDirectionalSprite& fourDirectionalSprite = get(spriteId, mData.tFourDirectionalSprite);
            ++fourDirectionalSprite.animationClock;
        }

    }, mData.tObjectSpriteInstance);
}
