#include "animationutil.hpp"

int32_t addSpriteAnimation(StringHash hash, SpriteAnimation animation, GameData& data)
{
    int32_t newId = insert(std::move(animation), data.tSpriteAnimation).id;
    insert(SpriteAnimationIndex{hash, newId}, data.tSpriteAnimationIndex);
    return newId;
}
