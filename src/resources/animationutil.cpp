#include "animationutil.hpp"

int32_t addSpriteAnimation(StringHash hash, SpriteAnimation animation, GameData& data)
{
    int32_t newId = insert(std::move(animation), data.tSpriteAnimation).id;
    insert(SpriteAnimationIndex{hash, newId}, data.tSpriteAnimationIndex);
    return newId;
}

th::Optional<int32_t> findAnimation(StringHash hash, GameData& data)
{
    auto found = findOne([&](int32_t id, const SpriteAnimationIndex& animationIndex)
    {
        return animationIndex.hash == hash;
    }, data.tSpriteAnimationIndex);

    if(found)
        return {found->id};
    else
        return {};
}
