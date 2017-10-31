#include "entitylogic.hpp"
#include <dpx/foreach.hpp>
#include <dpx/get.hpp>
#include <dpx/clear.hpp>
#include <dpx/join.hpp>
#include "entityutil.hpp"
#include <gamedata.hpp>
#include <spr/random/random.hpp>
#include <startupconstants.hpp>
#include <spr/data/position.hpp>
#include <spr/data/physics.hpp>
#include <spr/data/worldposition.hpp>
#include <spr/data/animatedsprite.hpp>
#include <spr/data/fourdirectionalsprite.hpp>
#include <spr/data/entitycollider.hpp>
#include <data/autowalk.hpp>
#include <data/leftsidecleanup.hpp>
#include <data/splashlanding.hpp>
#include <child/child.hpp>
#include <constants/world.hpp>

EntityLogic::EntityLogic(GameData& data) :
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

    // spawn new children
    if(spr::randomChance(0.01f, mData.randomEngine)) 
    {
        float ySpawnPos = spr::randomFloatRange(mData.bounds.top, mData.bounds.bottom, mData.randomEngine);
        glm::vec3 childSpawnPosition = {425.0f, ySpawnPos, 0.0f};
        int32_t health = 3;
        ChildType type = ChildType::Girl;
        spawnChild(childSpawnPosition, -1.0f, health, type, mData);
        //dpx::TableId newChildId = spawnChild(childSpawnPosition, -1.0f, health, type);
    }

    // update left-side cleanups
    dpx::join([&](dpx::TableId id, const spr::WorldPosition& position, const LeftSideCleanup&)
    {
        if(position.coordinate.x < -400.0f)
            removeEntityData(id, mData);
    }, *mData.spr.tWorldPosition, *mData.game.tLeftSideCleanup);

    dpx::join([&](int32_t id, AutoWalk& autoWalk, spr::Position& position)
    { // for everything with autowalk
        glm::vec3& pos = position.coordinate;
        if(autoWalk.on) 
        { 
            const float vel = autoWalk.velocity;
            pos.x += vel;
        }
    }, *mData.game.tAutoWalk, *mData.spr.tPosition);

    dpx::join([&](int32_t id, AutoWalk& autoWalk, spr::Position& position, spr::Physics& physics)
    { // for every child every frame
        glm::vec3& pos = position.coordinate;
        if(autoWalk.on) 
        { 
            physics.velocity = {0.0f, 0.0f};
            physics.acceleration = {0.0f, 0.0f};
        }
        else
        { // flying away
            if(pos.y >= autoWalk.walkLineY)
            { // check they don't fall below walking line
                pos.y = autoWalk.walkLineY;
                autoWalk.on = true;
            }
            else 
            {
                physics.acceleration.y = 0.1f;
            }
        }
    }, *mData.game.tAutoWalk, *mData.spr.tPosition, *mData.spr.tPhysics);

    dpx::join([&](int32_t id, SplashLanding& splashLanding, spr::Position& position, spr::Physics& physics)
    { // for every blood particle every frame
        glm::vec3& pos = position.coordinate;
        if(pos.y >= splashLanding.landingYCoordinate)
        { // check they don't fall below splashing line
            pos.y = splashLanding.landingYCoordinate;
            physics.acceleration = {0.0f, 0.0f};
            physics.velocity = {0.0f, 0.0f};
        }
    }, *mData.game.tSplashLanding, *mData.spr.tPosition, *mData.spr.tPhysics);

    // remove entities
    forEach([&](int32_t id)
    {
        removeEntityData(id, mData);
    }, mData.entitiesToRemove);

    clear(mData.entitiesToRemove);
}

void EntityLogic::updateSpatialTree()
{
    join([&] (int32_t id, const spr::WorldPosition& position, const spr::EntityCollider&)
    {
        float halfSpatialStorageSize = mData.c->world->spatialStorageSize / 2.0f;

        if(withinSpatialBounds(spr::xy(position.coordinate), mData))
        {
            mData.spatialEntityStorage.move(static_cast<int32_t>(id), {position.coordinate.x + halfSpatialStorageSize, position.coordinate.y + halfSpatialStorageSize});
        }
    }, *mData.spr.tWorldPosition, *mData.spr.tEntityCollider);
}
