#include "entityutil.hpp"
#include <dpx/insert.hpp>
#include <dpx/erase.hpp>
#include <dpx/has.hpp>
#include <dpx/get.hpp>
#include <dpx/find.hpp>

#include <spr/data/position.hpp>
#include <spr/data/hitbox.hpp>
#include <spr/data/entitycollider.hpp>
#include <spr/data/sceneparent.hpp>
#include <spr/entity/entityutil.hpp>
#include <constants/world.hpp>
#include <data/health.hpp>
#include <gamedata.hpp>

int32_t addEntity(spr::EntityProperties properties, GameData& data)
{
    int32_t newId = spr::addEntity(properties, data.spr);

    auto entityCollider = properties.find("entity_collider"_hash);
    if(entityCollider != properties.end())
    {
        spr::QuadTree::Vector spatialTreePosition;

        spr::Position position = properties.at("position"_hash).get<spr::Position>();

        auto hitboxIter = properties.find("hitbox"_hash);
        TH_ASSERT(hitboxIter != properties.end(), "entity_collider must have hitbox");
        const spr::Hitbox& hitbox = hitboxIter->second.get<spr::Hitbox>();


        //if the entity is spawned outside of the quadtree range, we just give it a random position in it.
        float halfStorageSize = data.c->world->spatialStorageSize / 2.0f;
        if(!withinSpatialBounds(spr::xy(position.coordinate), data))
            spatialTreePosition = {};
        else
            spatialTreePosition = {position.coordinate.x + halfStorageSize, position.coordinate.y + halfStorageSize};

        data.spatialEntityStorage.add(static_cast<int32_t>(newId), spatialTreePosition, {hitbox.aabb.size.x, hitbox.aabb.size.y});
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
    if(has(entityId, *data.spr.tEntityCollider))
        data.spatialEntityStorage.remove(static_cast<int32_t>(entityId));

    spr::removeEntityData(entityId, data.spr);

    //tables
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
