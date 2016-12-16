#include "entityutil.hpp"
#include <data.hpp>

int32_t addEntity(Entity entity, GameData& data)
{
    int32_t newId = insert(std::move(entity.position), data.tPosition).id;

    return newId;
}
