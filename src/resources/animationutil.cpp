#include "animationutil.hpp"
#include <spr/data/spriteanimationindex.hpp>
#include <spr/data/fourdirectionalanimationgroupindex.hpp>

int32_t addSpriteAnimation(spr::StringHash hash, spr::SpriteAnimation animation, spr::TableModule& tables)
{
    int32_t newId = insert(std::move(animation), tables.t<spr::TSpriteAnimation>()).id;
    insert(spr::SpriteAnimationIndex{hash, newId}, tables.t<spr::TSpriteAnimationIndex>());
    return newId;
}

th::Optional<int32_t> findAnimation(spr::StringHash hash, spr::TableModule& tables)
{
    auto found = findOne([&](int32_t id, const spr::SpriteAnimationIndex& animationIndex)
    {
        return animationIndex.hash == hash;
    }, tables.t<spr::TSpriteAnimationIndex>());

    if(found)
        return {found->id};
    else
        return {};
}

int32_t addFourDirectionalAnimationGroup(spr::StringHash hash, spr::FourDirectionalAnimationGroup animationGroup, spr::TableModule& tables)
{
    int32_t newId = insert(std::move(animationGroup), tables.t<spr::TFourDirectionalAnimationGroup>()).id;
    insert(spr::FourDirectionalAnimationGroupIndex{hash, newId}, tables.t<spr::TFourDirectionalAnimationGroupIndex>());
    return newId;
}

th::Optional<int32_t> findFourDirectionalAnimationGroup(spr::StringHash hash, spr::TableModule& tables)
{
    auto found = findOne([&](int32_t id, const spr::FourDirectionalAnimationGroupIndex& animationGroupIndex)
    {
        return animationGroupIndex.hash == hash;
    }, tables.t<spr::TFourDirectionalAnimationGroupIndex>());

    if(found)
        return {found->id};
    else
        return {};
}
