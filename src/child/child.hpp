#pragma once
#include <gamedata.hpp>
#include <dpx/tableid.hpp>
#include <spr/glm.hpp>

enum ChildType
{
    Girl,
    Boy,
};

dpx::TableId spawnChild(const glm::vec3& childSpawnPosition, const float speed, const int32_t health, const ChildType type, GameData& data);
