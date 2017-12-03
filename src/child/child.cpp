#include <child/child.hpp>
#include <data/datatables.hpp>
#include <data/angularphysics.hpp>
#include <data/autowalk.hpp>
#include <data/health.hpp>
#include <data/leftsidecleanup.hpp>
#include <entity/entityutil.hpp>

#include <spr/data/entitycollider.hpp>
#include <spr/data/hitbox.hpp>
#include <spr/data/obbcollider.hpp>
#include <spr/data/physics.hpp>
#include <spr/data/rotation.hpp>
#include <spr/data/tables.hpp>
#include <spr/entity/entityproperties.hpp>
#include <spr/entity/spawnentity.hpp>
#include <spr/resources/texture.hpp>

dpx::TableId spawnChild(const glm::vec3& childSpawnPosition, const float speed, const int32_t health, const ChildType type, GameData& data)
{
    spr::EntityProperties newChild = spr::createSpriteProperties(childSpawnPosition, {}, {}, {48.0f, 48.0f}, *spr::findTexture("christmas.child"_hash, data.spr), data.renderData.mainShader, data.renderData.mainViewport, data.renderData.worldCamera);
    newChild["physics"_hash] = spr::Physics{glm::vec2(0.0f, 0.0f), glm::vec2(0.0f, 0.1f)};
    newChild["auto_walk"_hash] = AutoWalk{true, speed, childSpawnPosition.y};
    newChild["entity_collider"_hash] = spr::EntityCollider{spr::EntityCollider::ObbCollider, spr::CollisionType::Trigger, {}};
    newChild["obb_collider"_hash] = spr::ObbCollider{glm::vec2(32.0f, 48.0f)};
    newChild["hitbox"_hash] = spr::Hitbox{{glm::vec2(-16.0f, -24.0f), glm::vec2(10.0f, 24.0f)}};
    newChild["health"_hash] = Health{health};
    newChild["left_side_cleanup"_hash] = LeftSideCleanup{};
    return addEntity(newChild, data);
}
