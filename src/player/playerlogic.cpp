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
    ////set world camera
    //glm::vec2 playerPosition = get(*mData.playerBrain, *mData.spr.tPosition).coordinate;
    //spr::Camera& worldCam = get(mData.worldCamera, *mData.spr.tCamera);
    //worldCam.translation = {playerPosition.x, playerPosition.y, 100.0f};
    if(mData.ongoingPlayerActions.count(PlayerAction::Punch))
    {
        float& acc = get(mData.armAnchorId, *mData.game.tAngularPhysics).acceleration;
        acc = 0.009f;
    }
    else {
        float& acc = get(mData.armAnchorId, *mData.game.tAngularPhysics).acceleration;
        float& vel = get(mData.armAnchorId, *mData.game.tAngularPhysics).velocity;
        float& rotation = get(mData.armAnchorId, *mData.spr.tRotation).angle;
        if(acc <= 0.00f)
        {
            acc = 0.00f;
            if(vel <= 0.00f)
            {
                vel = 0.00f;
            }
            else
            {
                vel -= 0.002f;
            }
        }
        else
        {
            acc -= 0.001f;
        }
        //rotation = 0.0f;
    }
    if(mData.ongoingPlayerActions.count(PlayerAction::Left))
    {
        glm::vec3& coordinate = get(mData.santaId, *mData.spr.tPosition).coordinate;
        coordinate.x -= 1.0f;
    }
    if(mData.ongoingPlayerActions.count(PlayerAction::Right))
    {
        glm::vec3& coordinate = get(mData.santaId, *mData.spr.tPosition).coordinate;
        coordinate.x += 1.0f;
    }
    if(mData.ongoingPlayerActions.count(PlayerAction::Up))
    {
        glm::vec3& coordinate = get(mData.santaId, *mData.spr.tPosition).coordinate;
        coordinate.y -= 2.0f;
    }
    if(mData.ongoingPlayerActions.count(PlayerAction::Down))
    {
        glm::vec3& coordinate = get(mData.santaId, *mData.spr.tPosition).coordinate;
        coordinate.y += 2.0f;
    }
}
