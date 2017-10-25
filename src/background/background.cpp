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
    int32_t bgSegmentCount = std::static_cast<int32_t>(mData.mainViewport.width / bgSegmentWidth) + 1;
    float leftmostX = -(std::static_cast<float>(bgSegmentCount) / 2.0f) * bgSegmentWidth;
    for(int32_t i = 0; i < bgSegmentCount; ++i)
    {
        // choose random texture
        //int32_t texture = spr::randomIntRange(0, mData.bgSegments.length, mData.randomEngine);
        //*spr::findTexture("bg"_hash, mData.spr)
        float posX = leftmostX + (bgSegmentWidth * i);
        float posY = 0.0f;
        float speed = mData.scrollSpeed;
        spr::EntityProperties bgSegment = spr::createSpriteProperties({posX, posY, -1.0f}, {}, {}, {bgSegmentWidth, 400.0f}, texture, mData.spr), mData.mainShader, mData.mainViewport, mData.worldCamera);
        bgSegment["left_side_cleanup"_hash] = LeftSideCleanup{posX - bgSegmentWidth};
        bgSegment["auto_walk"_hash] = AutoWalk{true, speed, posY};
        addEntity(bg, mData);
    }
}

void checkNewBackground()
{
}
