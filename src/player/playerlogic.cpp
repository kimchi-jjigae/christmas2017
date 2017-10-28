#include "playerlogic.hpp"
#include <data/angularphysics.hpp>
#include <dpx/get.hpp>
#include <spr/data/position.hpp>
#include <spr/data/rotation.hpp>
#include <spr/data/camera.hpp>
#include <gamedata.hpp>

PlayerLogic::PlayerLogic(GameData& data):
    mData(data)
{
}

void PlayerLogic::update()
{
    (void)mData;
    if(mData.inputData.stoppedActions.count(PlayerAction::LoadPunch))
    { // upon the frame of punch releasing
        float& vel = get(mData.armAnchorId, *mData.game.tAngularPhysics).velocity;
        vel *= -2.0f;
    }
    else if(mData.inputData.startedActions.count(PlayerAction::LoadPunch))
    { // upon the frame of punch loading
        float& vel = get(mData.armAnchorId, *mData.game.tAngularPhysics).velocity;
        vel = 0.0f;
    }
    else
    {
        if(mData.inputData.ongoingActions.count(PlayerAction::LoadPunch))
        {
            // +ve charge up, -ve release
            float& acc = get(mData.armAnchorId, *mData.game.tAngularPhysics).acceleration;
            acc = 0.01f;
        }
        else {
            float& acc = get(mData.armAnchorId, *mData.game.tAngularPhysics).acceleration;
            float& vel = get(mData.armAnchorId, *mData.game.tAngularPhysics).velocity;
            acc = 0.01f; // keeps going even if nothing happens
            if(vel >= 0.00f)
            {
                vel = 0.00f;
            }
        }
    }
    if(mData.inputData.ongoingActions.count(PlayerAction::Left))
    {
        glm::vec3& coordinate = get(mData.santaId, *mData.spr.tPosition).coordinate;
        coordinate.x -= 1.0f;
    }
    if(mData.inputData.ongoingActions.count(PlayerAction::Right))
    {
        glm::vec3& coordinate = get(mData.santaId, *mData.spr.tPosition).coordinate;
        coordinate.x += 1.0f;
    }
    if(mData.inputData.ongoingActions.count(PlayerAction::Up))
    {
        glm::vec3& coordinate = get(mData.santaId, *mData.spr.tPosition).coordinate;
        coordinate.y -= 2.0f;
    }
    if(mData.inputData.ongoingActions.count(PlayerAction::Down))
    {
        glm::vec3& coordinate = get(mData.santaId, *mData.spr.tPosition).coordinate;
        coordinate.y += 2.0f;
    }
}
