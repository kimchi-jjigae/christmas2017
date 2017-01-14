#include <spr/debug/debuggui.hpp>
#include <spr/data/tables.hpp>
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
#include <spr/data/renderpassinstance.hpp>
#include <spr/data/view.hpp>
namespace spr
{
inline void showDataTables(th::Optional<int32_t>& clickedEntity, const spr::Tables& tables)
{
    showDataTables(clickedEntity
        ,*tables.tEntityStateMachine
        ,*tables.tEntityState
        ,*tables.tEntityStateIndex
        ,*tables.tEntityOrientation
        ,*tables.tPosition
        ,*tables.tHitbox
        ,*tables.tEntityCollider
        ,*tables.tTexture
        ,*tables.tTextureIndex
        ,*tables.tSpriteAnimation
        ,*tables.tSpriteAnimationIndex
        ,*tables.tFourDirectionalAnimationGroup
        ,*tables.tFourDirectionalAnimationGroupIndex
        ,*tables.tEntitySpriteInstance
        ,*tables.tSprite
        ,*tables.tFourDirectionalSprite
        ,*tables.tAnimatedSprite
        ,*tables.tEntityDirection
        ,*tables.tRenderPassInstance
        ,*tables.tView
    );
}
}
