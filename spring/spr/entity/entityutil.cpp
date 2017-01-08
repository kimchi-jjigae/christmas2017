#include "entityutil.hpp"
#include <spr/data/entityspriteinstance.hpp>
#include <spr/data/fourdirectionalsprite.hpp>

namespace spr
{
void setEntityFourDirectionalAnimationGroup(int32_t entityId, int32_t animationGroup, TableModule& tables)
{
    auto found = findOne([&](int32_t id, const spr::EntitySpriteInstance& objSpriteInstance)
    {
        return objSpriteInstance.entityId == entityId;
    }, tables.t<TEntitySpriteInstance>());

    TH_ASSERT(found, "trying to set four directional animation group on entity " << entityId << " which lacks an objSpriteInstance");
    TH_ASSERT(has(found->data.spriteId, tables.t<TFourDirectionalSprite>()), "trying to set four directional animation group on entity " << entityId << " which doesn't have a FourDirectionalSprite");
    FourDirectionalSprite& sprite = get(found->data.spriteId, tables.t<TFourDirectionalSprite>());

    sprite.animationGroup = animationGroup;
}
}
