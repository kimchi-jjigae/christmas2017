#include "entitylogic.hpp"
#include <dpx/foreach.hpp>
#include <dpx/get.hpp>
#include <dpx/clear.hpp>
#include <dpx/join.hpp>
#include "entityutil.hpp"
#include <gamedata.hpp>
#include <startupconstants.hpp>
#include <spr/data/position.hpp>
#include <spr/data/animatedsprite.hpp>
#include <spr/data/fourdirectionalsprite.hpp>
#include <spr/data/entitycollider.hpp>
#include <constants/world.hpp>

EntityLogic::EntityLogic(GameData& data):
    mData(data)
{
}

void EntityLogic::update()
{
    forEach([&](int32_t spriteId, spr::Sprite& sprite)
    {
        auto animatedSprite = findId(spriteId, *mData.spr.tAnimatedSprite);
        auto fourDirectionalSprite = findId(spriteId, *mData.spr.tFourDirectionalSprite);
        if(animatedSprite)
        {
            ++animatedSprite->animationClock;
        }
        else if(fourDirectionalSprite)
        {
            ++fourDirectionalSprite->animationClock;
        }
    }, *mData.spr.tSprite);

    forEach([&](int32_t id)
    {
        removeEntityData(id, mData);
    }, mData.entitiesToRemove);

    clear(mData.entitiesToRemove);
}

void EntityLogic::updateSpatialTree()
{
    join([&] (int32_t id, const spr::Position& position, const spr::EntityCollider&)
    {
        float halfSpatialStorageSize = mData.c->world->spatialStorageSize / 2.0f;

        if(withinSpatialBounds(spr::xy(position.coordinate), mData))
        {
            mData.spatialEntityStorage.move(static_cast<int32_t>(id), {position.coordinate.x + halfSpatialStorageSize, position.coordinate.y + halfSpatialStorageSize});
        }
    }, *mData.spr.tPosition, *mData.spr.tEntityCollider);
}
