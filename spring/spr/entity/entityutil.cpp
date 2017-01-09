#include "entityutil.hpp"
#include <spr/data/tables.hpp>
#include <spr/data/entityspriteinstance.hpp>
#include <spr/data/fourdirectionalsprite.hpp>

namespace spr
{
void setEntityFourDirectionalAnimationGroup(int32_t entityId, int32_t animationGroup, Tables& tables)
{
    auto found = findOne([&](int32_t id, const spr::EntitySpriteInstance& objSpriteInstance)
    {
        return objSpriteInstance.entityId == entityId;
    }, *tables.tEntitySpriteInstance);

    TH_ASSERT(found, "trying to set four directional animation group on entity " << entityId << " which lacks an objSpriteInstance");
    TH_ASSERT(has(found->data.spriteId, *tables.tFourDirectionalSprite), "trying to set four directional animation group on entity " << entityId << " which doesn't have a FourDirectionalSprite");
    FourDirectionalSprite& sprite = get(found->data.spriteId, *tables.tFourDirectionalSprite);

    sprite.animationGroup = animationGroup;
}
}
