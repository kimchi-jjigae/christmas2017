#include "animationutil.hpp"
#include <spr/data/spriteanimationindex.hpp>
#include <spr/data/fourdirectionalanimationgroupindex.hpp>

int32_t addSpriteAnimation(spr::StringHash hash, spr::SpriteAnimation animation, spr::Tables& tables)
{
    int32_t newId = insert(std::move(animation), *tables.tSpriteAnimation).id;
    insert(spr::SpriteAnimationIndex{hash, newId}, *tables.tSpriteAnimationIndex);
    return newId;
}

th::Optional<int32_t> findAnimation(spr::StringHash hash, spr::Tables& tables)
{
    auto found = findOne([&](int32_t id, const spr::SpriteAnimationIndex& animationIndex)
    {
        return animationIndex.hash == hash;
    }, *tables.tSpriteAnimationIndex);

    if(found)
        return {found->id};
    else
        return {};
}

int32_t addFourDirectionalAnimationGroup(spr::StringHash hash, spr::FourDirectionalAnimationGroup animationGroup, spr::Tables& tables)
{
    int32_t newId = insert(std::move(animationGroup), *tables.tFourDirectionalAnimationGroup).id;
    insert(spr::FourDirectionalAnimationGroupIndex{hash, newId}, *tables.tFourDirectionalAnimationGroupIndex);
    return newId;
}

th::Optional<int32_t> findFourDirectionalAnimationGroup(spr::StringHash hash, spr::Tables& tables)
{
    auto found = findOne([&](int32_t id, const spr::FourDirectionalAnimationGroupIndex& animationGroupIndex)
    {
        return animationGroupIndex.hash == hash;
    }, *tables.tFourDirectionalAnimationGroupIndex);

    if(found)
        return {found->id};
    else
        return {};
}
