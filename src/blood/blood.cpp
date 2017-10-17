#include <child/child.hpp>
#include <data/datatables.hpp>
#include <data/angularphysics.hpp>
#include <data/autowalk.hpp>
#include <data/health.hpp>
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

void spawnBloodSplash(const glm::vec3& childSpawnPosition, const float speed, const int32_t health, const ChildType type, GameData& data)
{
}

dpx::TableId spawnBloodParticle(const glm::vec3& position, const glm::vec2 velocity, float landingYPos, GameData& data)
{
    spr::EntityProperties newBlood = spr::createSpriteProperties(childSpawnPosition, {}, {}, {48.0f, 48.0f}, *spr::findTexture("child"_hash, data.spr), data.mainShader, data.mainViewport, data.worldCamera);
    newChild["physics"_hash] = spr::Physics{velocity, glm::vec2(0.0f, 0.1f)};
    newChild["splashLanding"_hash] = SplashLanding{yPos};
    newChild["entity_collider"_hash] = spr::EntityCollider{spr::EntityCollider::ObbCollider, spr::CollisionType::Trigger, {}};
    return addEntity(newBlood, data);
}
