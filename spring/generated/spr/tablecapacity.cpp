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

SprTablesCapacity sprTablesCapacity(const spr::Tables& tables)
{
    SprTablesCapacity capacity;
    capacity.entitystatemachineCapacity = tables.tEntityStateMachine->ids.capacity();
    capacity.entitystateCapacity = tables.tEntityState->ids.capacity();
    capacity.entitystateindexCapacity = tables.tEntityStateIndex->ids.capacity();
    capacity.entityorientationCapacity = tables.tEntityOrientation->ids.capacity();
    capacity.positionCapacity = tables.tPosition->ids.capacity();
    capacity.hitboxCapacity = tables.tHitbox->ids.capacity();
    capacity.entitycolliderCapacity = tables.tEntityCollider->ids.capacity();
    capacity.textureCapacity = tables.tTexture->ids.capacity();
    capacity.textureindexCapacity = tables.tTextureIndex->ids.capacity();
    capacity.spriteanimationCapacity = tables.tSpriteAnimation->ids.capacity();
    capacity.spriteanimationindexCapacity = tables.tSpriteAnimationIndex->ids.capacity();
    capacity.fourdirectionalanimationgroupCapacity = tables.tFourDirectionalAnimationGroup->ids.capacity();
    capacity.fourdirectionalanimationgroupindexCapacity = tables.tFourDirectionalAnimationGroupIndex->ids.capacity();
    capacity.entityspriteinstanceCapacity = tables.tEntitySpriteInstance->ids.capacity();
    capacity.spriteCapacity = tables.tSprite->ids.capacity();
    capacity.fourdirectionalspriteCapacity = tables.tFourDirectionalSprite->ids.capacity();
    capacity.animatedspriteCapacity = tables.tAnimatedSprite->ids.capacity();
    capacity.entitydirectionCapacity = tables.tEntityDirection->ids.capacity();
    return capacity;
}

void sprEnsureCapacity(size_t capacity, spr::Tables& tables)
{
    if(count(*tables.tEntityStateMachine) + capacity > tables.tEntityStateMachine->ids.capacity())
    {
        tables.tEntityStateMachine->ids.reserve(count(*tables.tEntityStateMachine) + capacity);
        tables.tEntityStateMachine->data.reserve(count(*tables.tEntityStateMachine) + capacity);
    }
    if(count(*tables.tEntityState) + capacity > tables.tEntityState->ids.capacity())
    {
        tables.tEntityState->ids.reserve(count(*tables.tEntityState) + capacity);
        tables.tEntityState->data.reserve(count(*tables.tEntityState) + capacity);
    }
    if(count(*tables.tEntityStateIndex) + capacity > tables.tEntityStateIndex->ids.capacity())
    {
        tables.tEntityStateIndex->ids.reserve(count(*tables.tEntityStateIndex) + capacity);
        tables.tEntityStateIndex->data.reserve(count(*tables.tEntityStateIndex) + capacity);
    }
    if(count(*tables.tEntityOrientation) + capacity > tables.tEntityOrientation->ids.capacity())
    {
        tables.tEntityOrientation->ids.reserve(count(*tables.tEntityOrientation) + capacity);
        tables.tEntityOrientation->data.reserve(count(*tables.tEntityOrientation) + capacity);
    }
    if(count(*tables.tPosition) + capacity > tables.tPosition->ids.capacity())
    {
        tables.tPosition->ids.reserve(count(*tables.tPosition) + capacity);
        tables.tPosition->data.reserve(count(*tables.tPosition) + capacity);
    }
    if(count(*tables.tHitbox) + capacity > tables.tHitbox->ids.capacity())
    {
        tables.tHitbox->ids.reserve(count(*tables.tHitbox) + capacity);
        tables.tHitbox->data.reserve(count(*tables.tHitbox) + capacity);
    }
    if(count(*tables.tEntityCollider) + capacity > tables.tEntityCollider->ids.capacity())
    {
        tables.tEntityCollider->ids.reserve(count(*tables.tEntityCollider) + capacity);
        tables.tEntityCollider->data.reserve(count(*tables.tEntityCollider) + capacity);
    }
    if(count(*tables.tTexture) + capacity > tables.tTexture->ids.capacity())
    {
        tables.tTexture->ids.reserve(count(*tables.tTexture) + capacity);
        tables.tTexture->data.reserve(count(*tables.tTexture) + capacity);
    }
    if(count(*tables.tTextureIndex) + capacity > tables.tTextureIndex->ids.capacity())
    {
        tables.tTextureIndex->ids.reserve(count(*tables.tTextureIndex) + capacity);
        tables.tTextureIndex->data.reserve(count(*tables.tTextureIndex) + capacity);
    }
    if(count(*tables.tSpriteAnimation) + capacity > tables.tSpriteAnimation->ids.capacity())
    {
        tables.tSpriteAnimation->ids.reserve(count(*tables.tSpriteAnimation) + capacity);
        tables.tSpriteAnimation->data.reserve(count(*tables.tSpriteAnimation) + capacity);
    }
    if(count(*tables.tSpriteAnimationIndex) + capacity > tables.tSpriteAnimationIndex->ids.capacity())
    {
        tables.tSpriteAnimationIndex->ids.reserve(count(*tables.tSpriteAnimationIndex) + capacity);
        tables.tSpriteAnimationIndex->data.reserve(count(*tables.tSpriteAnimationIndex) + capacity);
    }
    if(count(*tables.tFourDirectionalAnimationGroup) + capacity > tables.tFourDirectionalAnimationGroup->ids.capacity())
    {
        tables.tFourDirectionalAnimationGroup->ids.reserve(count(*tables.tFourDirectionalAnimationGroup) + capacity);
        tables.tFourDirectionalAnimationGroup->data.reserve(count(*tables.tFourDirectionalAnimationGroup) + capacity);
    }
    if(count(*tables.tFourDirectionalAnimationGroupIndex) + capacity > tables.tFourDirectionalAnimationGroupIndex->ids.capacity())
    {
        tables.tFourDirectionalAnimationGroupIndex->ids.reserve(count(*tables.tFourDirectionalAnimationGroupIndex) + capacity);
        tables.tFourDirectionalAnimationGroupIndex->data.reserve(count(*tables.tFourDirectionalAnimationGroupIndex) + capacity);
    }
    if(count(*tables.tEntitySpriteInstance) + capacity > tables.tEntitySpriteInstance->ids.capacity())
    {
        tables.tEntitySpriteInstance->ids.reserve(count(*tables.tEntitySpriteInstance) + capacity);
        tables.tEntitySpriteInstance->data.reserve(count(*tables.tEntitySpriteInstance) + capacity);
    }
    if(count(*tables.tSprite) + capacity > tables.tSprite->ids.capacity())
    {
        tables.tSprite->ids.reserve(count(*tables.tSprite) + capacity);
        tables.tSprite->data.reserve(count(*tables.tSprite) + capacity);
    }
    if(count(*tables.tFourDirectionalSprite) + capacity > tables.tFourDirectionalSprite->ids.capacity())
    {
        tables.tFourDirectionalSprite->ids.reserve(count(*tables.tFourDirectionalSprite) + capacity);
        tables.tFourDirectionalSprite->data.reserve(count(*tables.tFourDirectionalSprite) + capacity);
    }
    if(count(*tables.tAnimatedSprite) + capacity > tables.tAnimatedSprite->ids.capacity())
    {
        tables.tAnimatedSprite->ids.reserve(count(*tables.tAnimatedSprite) + capacity);
        tables.tAnimatedSprite->data.reserve(count(*tables.tAnimatedSprite) + capacity);
    }
    if(count(*tables.tEntityDirection) + capacity > tables.tEntityDirection->ids.capacity())
    {
        tables.tEntityDirection->ids.reserve(count(*tables.tEntityDirection) + capacity);
        tables.tEntityDirection->data.reserve(count(*tables.tEntityDirection) + capacity);
    }
}
}
