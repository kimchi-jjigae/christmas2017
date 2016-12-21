#include "entitylogic.hpp"

EntityLogic::EntityLogic(GameData& data):
    mData(data)
{
}

void EntityLogic::update()
{
    forEach([&](int32_t id, ObjectSpriteInstance& objectSprite)
    {
        Sprite& sprite = get(objectSprite.spriteId, mData.tSprite);       
        const Position& position = get(objectSprite.objectId, mData.tPosition);       

        sprite.position = position.coordinate + objectSprite.offset;
    }, mData.tObjectSpriteInstance);
}
