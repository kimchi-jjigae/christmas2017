#include "playerlogic.hpp"
#include <dpx/get.hpp>
#include <spr/data/position.hpp>
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
}
