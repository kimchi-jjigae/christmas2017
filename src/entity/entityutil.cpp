#include "entityutil.hpp"
#include <dpx/insert.hpp>
#include <dpx/erase.hpp>
#include <dpx/has.hpp>
#include <dpx/get.hpp>
#include <dpx/find.hpp>
#include <spr/data/sceneparent.hpp>
#include <spr/data/position.hpp>
#include <spr/data/worldposition.hpp>
#include <spr/data/worldrotation.hpp>
#include <spr/data/name.hpp>
#include <spr/data/spritecolor.hpp>
#include <spr/data/drawableaddutil.hpp>
#include <spr/data/animatedsprite.hpp>
#include <spr/data/entitycollider.hpp>
#include <spr/data/entitycollideraddutil.hpp>
#include <spr/data/obbcollider.hpp>
#include <spr/data/circlecollider.hpp>
#include <spr/data/entityorientation.hpp>
#include <spr/data/entitystatemachine.hpp>
#include <spr/data/entitycollideraddutil.hpp>
#include <spr/data/hitbox.hpp>
#include <spr/data/dirtyhitbox.hpp>
#include <spr/data/dirtyworld.hpp>
#include <spr/data/rotation.hpp>
#include <spr/data/physics.hpp>
#include <spr/data/fourdirectionalsprite.hpp>
#include <spr/entitystates/stateutil.hpp>

#include <constants/world.hpp>
#include <data/health.hpp>
#include <gamedata.hpp>

int32_t addEntity(EntityProperties properties, GameData& data)
{
    //spr tables

    const auto& parentIter = properties.find("scene_parent"_hash);
    int32_t newId = insert(parentIter == properties.end() ? spr::SceneParent{-1} : parentIter->second.get<spr::SceneParent>(), *data.spr.tSceneParent).id;
    spr::Position position = properties.at("position"_hash).get<spr::Position>();
    insert(newId, position, *data.spr.tPosition);
    insert(newId, properties.at("rotation"_hash).get<spr::Rotation>(), *data.spr.tRotation);
    insert(newId, {}, *data.spr.tWorldPosition);
    insert(newId, {}, *data.spr.tWorldRotation);
    insert(newId, {}, *data.spr.tDirtyWorld);
    insertOptional(newId, "name"_hash, properties, *data.spr.tName);
    insertOptional(newId, "orientation"_hash, properties, *data.spr.tEntityOrientation);

    insertOptional(newId, "physics"_hash, properties, *data.spr.tPhysics);

    auto hitboxIter = properties.find("hitbox"_hash);
    if(hitboxIter != properties.end())
    {
        const spr::Hitbox& hitbox = hitboxIter->second.get<spr::Hitbox>();
        insert(newId, hitbox, *data.spr.tHitbox);
        insert(newId, {}, *data.spr.tDirtyHitbox);
    }

    auto entityCollider = properties.find("entity_collider"_hash);

    if(entityCollider != properties.end())
    {
        TH_ASSERT(hitboxIter != properties.end(), "entity_collider must have hitbox");
        const spr::Hitbox& hitbox = hitboxIter->second.get<spr::Hitbox>();

        spr::QuadTree::Vector spatialTreePosition;

        //if the entity is spawned outside of the quadtree range, we just give it a random position in it.
        float halfStorageSize = data.c->world->spatialStorageSize / 2.0f;
        if(!withinSpatialBounds(position.coordinate, data))
            spatialTreePosition = {};
        else
            spatialTreePosition = {position.coordinate.x + halfStorageSize, position.coordinate.y + halfStorageSize};

        data.spatialEntityStorage.add(static_cast<int32_t>(newId), spatialTreePosition, {hitbox.aabb.size.x, hitbox.aabb.size.y});
        spr::EntityCollider collider = std::move(entityCollider->second.get<spr::EntityCollider>());

        if(collider.entityColliderType == spr::EntityCollider::_Base)
        {
            insert(newId, std::move(collider), *data.spr.tEntityCollider);
        }
        else if(collider.entityColliderType == spr::EntityCollider::ObbCollider)
        {
            spr::insertEntityCollider(newId, std::move(collider),
                    std::move(properties.at("obb_collider"_hash).get<spr::ObbCollider>()),
                    data.spr);
        }
        else if(collider.entityColliderType == spr::EntityCollider::CircleCollider)
        {
            spr::insertEntityCollider(newId, std::move(collider),
                    std::move(properties.at("circle_collider"_hash).get<spr::CircleCollider>()),
                    data.spr);
        }
    }

    auto sprite = properties.find("sprite"_hash);

    if(sprite != properties.end())
    {
        insertDrawable(newId, {}, sprite->second.get<spr::Sprite>(), data.spr);

        spr::Sprite& srite = get(newId, *data.spr.tSprite);

        auto animatedSprite = properties.find("animated_sprite"_hash);
        auto fourDirectionalSprite = properties.find("four_directional_sprite"_hash);

        if(animatedSprite != properties.end())
        {
            insert(newId, animatedSprite->second.get<spr::AnimatedSprite>(), *data.spr.tAnimatedSprite);
        }
        else if(fourDirectionalSprite != properties.end())
        {
            insert(newId, fourDirectionalSprite->second.get<spr::FourDirectionalSprite>(), *data.spr.tFourDirectionalSprite);
        }

        auto spriteColor = properties.find("sprite_color"_hash);

        if(spriteColor != properties.end())
        {
            insert(newId, spriteColor->second.get<spr::SpriteColor>(), *data.spr.tSpriteColor);
        }
    }

    if(properties.count("entity_state"_hash) != 0)
    {
        const auto& entityState = properties.at("entity_state"_hash).get<EntityState>();

        insert(spr::EntityStateMachine
        {
            newId,
            entityState.stateSet,
            getEntityState(entityState.stateSet, entityState.state, data.spr).id,
            {},
        }, *data.spr.tEntityStateMachine);
    }

    //game tables
    insertOptional(newId, "health"_hash, properties, *data.game.tHealth);

    return newId;
}

void removeEntity(int32_t entityId, GameData& data)
{
    TH_ASSERT(has(entityId, *data.spr.tSceneParent) , "Removing nonexisting entity " << entityId);
    if(!has(entityId, data.entitiesToRemove))
    {
        insert(entityId, data.entitiesToRemove);
    }
}

void removeEntityData(int32_t entityId, GameData& data)
{
    erase(entityId, *data.spr.tPosition);
    erase(entityId, *data.spr.tRotation);
    erase(entityId, *data.spr.tSceneParent);
    erase(entityId, *data.spr.tWorldPosition);
    erase(entityId, *data.spr.tWorldRotation);
    erase(entityId, *data.spr.tName);
    erase(entityId, *data.spr.tEntityOrientation);
    erase(entityId, *data.spr.tPhysics);

    erase(entityId, *data.spr.tHitbox);
    erase(entityId, *data.spr.tDirtyHitbox);
    erase(entityId, *data.spr.tDirtyWorld);

    bool erasedEntityCollider = spr::eraseEntityCollider(entityId, data.spr);
    if(erasedEntityCollider)
        data.spatialEntityStorage.remove(static_cast<int32_t>(entityId));

    erase(entityId, *data.spr.tEntityStateMachine);

    spr::eraseDrawable(entityId, data.spr);
    erase(entityId, *data.spr.tAnimatedSprite);
    erase(entityId, *data.spr.tFourDirectionalSprite);
    erase(entityId, *data.spr.tSpriteColor);
    
    //game tables
    erase(entityId, *data.game.tHealth);
}

void clearAllCurrentEntities(GameData& data)
{
    forEach([&] (int32_t id, const spr::Position& position)
    {
        removeEntity(id, data);
    }, *data.spr.tPosition);
}

bool withinSpatialBounds(glm::vec2 position, GameData& data)
{
    if(!withinSpatialBoundsX(position.x, data) || !withinSpatialBoundsY(position.y, data))
        return false;
    else
        return true;
}

bool withinSpatialBoundsX(float x, GameData& data)
{
    float halfSpatialStorageSize = data.c->world->spatialStorageSize / 2.0f;

    if(x < -halfSpatialStorageSize + 1.0f || x > halfSpatialStorageSize - 1.0f)
        return false;
    else
        return true;
}

bool withinSpatialBoundsY(float y, GameData& data)
{
    float halfSpatialStorageSize = data.c->world->spatialStorageSize / 2.0f;

    if(y < -halfSpatialStorageSize + 1.0f || y > halfSpatialStorageSize - 1.0f)
        return false;
    else
        return true;
}
