#include <background/background.hpp>
#include <data/datatables.hpp>
#include <data/angularphysics.hpp>
#include <data/autowalk.hpp>
#include <data/health.hpp>
#include <data/leftsidecleanup.hpp>
#include <entity/entityutil.hpp>

#include <spr/data/tables.hpp>
#include <spr/entity/entityproperties.hpp>
#include <spr/entity/spawnentity.hpp>
#include <spr/resources/texture.hpp>


void setupBackground(GameData& data)
{
    float bgSegmentWidth = 64.0f;
    //int32_t bgSegmentCount = static_cast<int32_t>(600.0f / bgSegmentWidth) + 1;
    int32_t bgSegmentCount = static_cast<int32_t>(data.screenSize.x / bgSegmentWidth) + 1;
    float leftmostX = -(static_cast<float>(bgSegmentCount) / 2.0f) * bgSegmentWidth;
    for(int32_t i = 0; i < bgSegmentCount; ++i)
    {
        // choose random texture
        //int32_t texture = spr::randomIntRange(0, data.bgSegments.length, data.randomEngine);
        //*spr::findTexture("christmas.bg"_hash, data.spr)
        int32_t texture = *spr::findTexture("christmas.bg"_hash, data.spr);
        float posX = leftmostX + (bgSegmentWidth * i);
        float posY = 0.0f;
        float speed = data.scrollSpeed;
        spr::EntityProperties bgSegment = spr::createSpriteProperties({posX, posY, -1.0f}, {}, {}, {bgSegmentWidth, 400.0f}, texture, data.renderData.mainShader, data.renderData.mainViewport, data.renderData.worldCamera);
        bgSegment["left_side_cleanup"_hash] = LeftSideCleanup{posX - bgSegmentWidth};
        bgSegment["auto_walk"_hash] = AutoWalk{true, speed, posY};
        addEntity(bgSegment, data);
    }
}

void checkNewBackground()
{
}
