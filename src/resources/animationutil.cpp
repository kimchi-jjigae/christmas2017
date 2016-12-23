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

int32_t addFourDirectionalAnimationGroup(StringHash hash, FourDirectionalAnimationGroup animationGroup, GameData& data)
{
    int32_t newId = insert(std::move(animationGroup), data.tFourDirectionalAnimationGroup).id;
    insert(FourDirectionalAnimationGroupIndex{hash, newId}, data.tFourDirectionalAnimationGroupIndex);
    return newId;
}

th::Optional<int32_t> findFourDirectionalAnimationGroup(StringHash hash, GameData& data)
{
    auto found = findOne([&](int32_t id, const FourDirectionalAnimationGroupIndex& animationGroupIndex)
    {
        return animationGroupIndex.hash == hash;
    }, data.tFourDirectionalAnimationGroupIndex);

    if(found)
        return {found->id};
    else
        return {};
}
