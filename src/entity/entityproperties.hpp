#pragma once
#include <spr/color/color.hpp>
#include <spr/glm.hpp>
#include <spr/data/sprite.hpp>
#include <unordered_map>
#include <spr/hash/stringhash.hpp>
#include <thero/any.hpp>

using EntityProperties = std::unordered_map<spr::StringHash, th::Any>;

void applyOverrides(const EntityProperties& overrides, EntityProperties& target);

template<typename DataTable>
void insertOptional(spr::StringHash hash, const EntityProperties& properties, DataTable& table)
{
    auto iter = properties.find(hash);

    if(iter != properties.end())
    {
        insert(iter->second.get<typename DataTable::Type>(), table);
    }
}

template<typename DataTable>
void insertOptional(dpx::TableId id, spr::StringHash hash, const EntityProperties& properties, DataTable& table)
{
    auto iter = properties.find(hash);

    if(iter != properties.end())
    {
        insert(id, iter->second.get<typename DataTable::Type>(), table);
    }
}

//this EntityState doesn't really belong here. hacky hack hack FIXI
struct EntityState
{
    spr::StringHash stateSet;
    spr::StringHash state;
};
