#include "tablecapacity.hpp"
#include <spr/data/entitystatemachine.hpp>
#include <spr/data/entitystate.hpp>
#include <spr/data/entitystateindex.hpp>
#include <spr/data/entityorientation.hpp>
#include <spr/data/position.hpp>
#include <spr/data/hitbox.hpp>
#include <spr/data/entitycollider.hpp>
#include <spr/data/texture.hpp>
#include <spr/data/textureindex.hpp>
#include <spr/data/spriteanimation.hpp>
#include <spr/data/spriteanimationindex.hpp>
#include <spr/data/fourdirectionalanimationgroup.hpp>
#include <spr/data/fourdirectionalanimationgroupindex.hpp>
#include <spr/data/entityspriteinstance.hpp>
#include <spr/data/sprite.hpp>
#include <spr/data/fourdirectionalsprite.hpp>
#include <spr/data/animatedsprite.hpp>
#include <spr/data/entitydirection.hpp>
namespace spr
{
bool operator==(const SprTablesCapacity& a, const SprTablesCapacity& b)
{
    return
    a.entitystatemachineCapacity == b.entitystatemachineCapacity &&
    a.entitystateCapacity == b.entitystateCapacity &&
    a.entitystateindexCapacity == b.entitystateindexCapacity &&
    a.entityorientationCapacity == b.entityorientationCapacity &&
    a.positionCapacity == b.positionCapacity &&
    a.hitboxCapacity == b.hitboxCapacity &&
    a.entitycolliderCapacity == b.entitycolliderCapacity &&
    a.textureCapacity == b.textureCapacity &&
    a.textureindexCapacity == b.textureindexCapacity &&
    a.spriteanimationCapacity == b.spriteanimationCapacity &&
    a.spriteanimationindexCapacity == b.spriteanimationindexCapacity &&
    a.fourdirectionalanimationgroupCapacity == b.fourdirectionalanimationgroupCapacity &&
    a.fourdirectionalanimationgroupindexCapacity == b.fourdirectionalanimationgroupindexCapacity &&
    a.entityspriteinstanceCapacity == b.entityspriteinstanceCapacity &&
    a.spriteCapacity == b.spriteCapacity &&
    a.fourdirectionalspriteCapacity == b.fourdirectionalspriteCapacity &&
    a.animatedspriteCapacity == b.animatedspriteCapacity &&
    a.entitydirectionCapacity == b.entitydirectionCapacity &&
    true;
}

bool operator!=(const SprTablesCapacity& a, const SprTablesCapacity& b)
{
    return !(a == b);
}

SprTablesCapacity sprTablesCapacity(const spr::TableModule& tables)
{
    SprTablesCapacity capacity;
    capacity.entitystatemachineCapacity = tables.t<TEntityStateMachine>().ids.capacity();
    capacity.entitystateCapacity = tables.t<TEntityState>().ids.capacity();
    capacity.entitystateindexCapacity = tables.t<TEntityStateIndex>().ids.capacity();
    capacity.entityorientationCapacity = tables.t<TEntityOrientation>().ids.capacity();
    capacity.positionCapacity = tables.t<TPosition>().ids.capacity();
    capacity.hitboxCapacity = tables.t<THitbox>().ids.capacity();
    capacity.entitycolliderCapacity = tables.t<TEntityCollider>().ids.capacity();
    capacity.textureCapacity = tables.t<TTexture>().ids.capacity();
    capacity.textureindexCapacity = tables.t<TTextureIndex>().ids.capacity();
    capacity.spriteanimationCapacity = tables.t<TSpriteAnimation>().ids.capacity();
    capacity.spriteanimationindexCapacity = tables.t<TSpriteAnimationIndex>().ids.capacity();
    capacity.fourdirectionalanimationgroupCapacity = tables.t<TFourDirectionalAnimationGroup>().ids.capacity();
    capacity.fourdirectionalanimationgroupindexCapacity = tables.t<TFourDirectionalAnimationGroupIndex>().ids.capacity();
    capacity.entityspriteinstanceCapacity = tables.t<TEntitySpriteInstance>().ids.capacity();
    capacity.spriteCapacity = tables.t<TSprite>().ids.capacity();
    capacity.fourdirectionalspriteCapacity = tables.t<TFourDirectionalSprite>().ids.capacity();
    capacity.animatedspriteCapacity = tables.t<TAnimatedSprite>().ids.capacity();
    capacity.entitydirectionCapacity = tables.t<TEntityDirection>().ids.capacity();
    return capacity;
}

void sprEnsureCapacity(size_t capacity, spr::TableModule& tables)
{
    if(tables.t<TEntityStateMachine>().ids.size() + capacity > tables.t<TEntityStateMachine>().ids.capacity())
    {
        tables.t<TEntityStateMachine>().ids.reserve(tables.t<TEntityStateMachine>().ids.size() + capacity);
        tables.t<TEntityStateMachine>().data.reserve(tables.t<TEntityStateMachine>().data.size() + capacity);
    }
    if(tables.t<TEntityState>().ids.size() + capacity > tables.t<TEntityState>().ids.capacity())
    {
        tables.t<TEntityState>().ids.reserve(tables.t<TEntityState>().ids.size() + capacity);
        tables.t<TEntityState>().data.reserve(tables.t<TEntityState>().data.size() + capacity);
    }
    if(tables.t<TEntityStateIndex>().ids.size() + capacity > tables.t<TEntityStateIndex>().ids.capacity())
    {
        tables.t<TEntityStateIndex>().ids.reserve(tables.t<TEntityStateIndex>().ids.size() + capacity);
        tables.t<TEntityStateIndex>().data.reserve(tables.t<TEntityStateIndex>().data.size() + capacity);
    }
    if(tables.t<TEntityOrientation>().ids.size() + capacity > tables.t<TEntityOrientation>().ids.capacity())
    {
        tables.t<TEntityOrientation>().ids.reserve(tables.t<TEntityOrientation>().ids.size() + capacity);
        tables.t<TEntityOrientation>().data.reserve(tables.t<TEntityOrientation>().data.size() + capacity);
    }
    if(tables.t<TPosition>().ids.size() + capacity > tables.t<TPosition>().ids.capacity())
    {
        tables.t<TPosition>().ids.reserve(tables.t<TPosition>().ids.size() + capacity);
        tables.t<TPosition>().data.reserve(tables.t<TPosition>().data.size() + capacity);
    }
    if(tables.t<THitbox>().ids.size() + capacity > tables.t<THitbox>().ids.capacity())
    {
        tables.t<THitbox>().ids.reserve(tables.t<THitbox>().ids.size() + capacity);
        tables.t<THitbox>().data.reserve(tables.t<THitbox>().data.size() + capacity);
    }
    if(tables.t<TEntityCollider>().ids.size() + capacity > tables.t<TEntityCollider>().ids.capacity())
    {
        tables.t<TEntityCollider>().ids.reserve(tables.t<TEntityCollider>().ids.size() + capacity);
        tables.t<TEntityCollider>().data.reserve(tables.t<TEntityCollider>().data.size() + capacity);
    }
    if(tables.t<TTexture>().ids.size() + capacity > tables.t<TTexture>().ids.capacity())
    {
        tables.t<TTexture>().ids.reserve(tables.t<TTexture>().ids.size() + capacity);
        tables.t<TTexture>().data.reserve(tables.t<TTexture>().data.size() + capacity);
    }
    if(tables.t<TTextureIndex>().ids.size() + capacity > tables.t<TTextureIndex>().ids.capacity())
    {
        tables.t<TTextureIndex>().ids.reserve(tables.t<TTextureIndex>().ids.size() + capacity);
        tables.t<TTextureIndex>().data.reserve(tables.t<TTextureIndex>().data.size() + capacity);
    }
    if(tables.t<TSpriteAnimation>().ids.size() + capacity > tables.t<TSpriteAnimation>().ids.capacity())
    {
        tables.t<TSpriteAnimation>().ids.reserve(tables.t<TSpriteAnimation>().ids.size() + capacity);
        tables.t<TSpriteAnimation>().data.reserve(tables.t<TSpriteAnimation>().data.size() + capacity);
    }
    if(tables.t<TSpriteAnimationIndex>().ids.size() + capacity > tables.t<TSpriteAnimationIndex>().ids.capacity())
    {
        tables.t<TSpriteAnimationIndex>().ids.reserve(tables.t<TSpriteAnimationIndex>().ids.size() + capacity);
        tables.t<TSpriteAnimationIndex>().data.reserve(tables.t<TSpriteAnimationIndex>().data.size() + capacity);
    }
    if(tables.t<TFourDirectionalAnimationGroup>().ids.size() + capacity > tables.t<TFourDirectionalAnimationGroup>().ids.capacity())
    {
        tables.t<TFourDirectionalAnimationGroup>().ids.reserve(tables.t<TFourDirectionalAnimationGroup>().ids.size() + capacity);
        tables.t<TFourDirectionalAnimationGroup>().data.reserve(tables.t<TFourDirectionalAnimationGroup>().data.size() + capacity);
    }
    if(tables.t<TFourDirectionalAnimationGroupIndex>().ids.size() + capacity > tables.t<TFourDirectionalAnimationGroupIndex>().ids.capacity())
    {
        tables.t<TFourDirectionalAnimationGroupIndex>().ids.reserve(tables.t<TFourDirectionalAnimationGroupIndex>().ids.size() + capacity);
        tables.t<TFourDirectionalAnimationGroupIndex>().data.reserve(tables.t<TFourDirectionalAnimationGroupIndex>().data.size() + capacity);
    }
    if(tables.t<TEntitySpriteInstance>().ids.size() + capacity > tables.t<TEntitySpriteInstance>().ids.capacity())
    {
        tables.t<TEntitySpriteInstance>().ids.reserve(tables.t<TEntitySpriteInstance>().ids.size() + capacity);
        tables.t<TEntitySpriteInstance>().data.reserve(tables.t<TEntitySpriteInstance>().data.size() + capacity);
    }
    if(tables.t<TSprite>().ids.size() + capacity > tables.t<TSprite>().ids.capacity())
    {
        tables.t<TSprite>().ids.reserve(tables.t<TSprite>().ids.size() + capacity);
        tables.t<TSprite>().data.reserve(tables.t<TSprite>().data.size() + capacity);
    }
    if(tables.t<TFourDirectionalSprite>().ids.size() + capacity > tables.t<TFourDirectionalSprite>().ids.capacity())
    {
        tables.t<TFourDirectionalSprite>().ids.reserve(tables.t<TFourDirectionalSprite>().ids.size() + capacity);
        tables.t<TFourDirectionalSprite>().data.reserve(tables.t<TFourDirectionalSprite>().data.size() + capacity);
    }
    if(tables.t<TAnimatedSprite>().ids.size() + capacity > tables.t<TAnimatedSprite>().ids.capacity())
    {
        tables.t<TAnimatedSprite>().ids.reserve(tables.t<TAnimatedSprite>().ids.size() + capacity);
        tables.t<TAnimatedSprite>().data.reserve(tables.t<TAnimatedSprite>().data.size() + capacity);
    }
    if(tables.t<TEntityDirection>().ids.size() + capacity > tables.t<TEntityDirection>().ids.capacity())
    {
        tables.t<TEntityDirection>().ids.reserve(tables.t<TEntityDirection>().ids.size() + capacity);
        tables.t<TEntityDirection>().data.reserve(tables.t<TEntityDirection>().data.size() + capacity);
    }
}
}
