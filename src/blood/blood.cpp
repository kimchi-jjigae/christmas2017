#include <blood/blood.hpp>
#include <data/angularphysics.hpp>
#include <data/autowalk.hpp>
#include <data/datatables.hpp>
#include <data/health.hpp>
#include <data/splashlanding.hpp>
#include <entity/entityutil.hpp>
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/rotate_vector.hpp>

#include <spr/data/entitycollider.hpp>
#include <spr/data/hitbox.hpp>
#include <spr/data/obbcollider.hpp>
#include <spr/data/physics.hpp>
#include <spr/data/rotation.hpp>
#include <spr/data/tables.hpp>
#include <spr/entity/entityproperties.hpp>
#include <spr/entity/spawnentity.hpp>
#include <spr/random/random.hpp>
#include <spr/resources/texture.hpp>

void spawnBloodSplash(const glm::vec3& childSpawnPosition, const float landingYPos, const float speed, const int32_t amount, GameData& data)
{
    for(int32_t i = 0; i < amount; ++i)
    {
        glm::vec2 velocity = {speed, 0.0f};
        float rotation = spr::randomFloatRange(0.0f, 360.0f, data.randomEngine);
        velocity = glm::rotate(velocity, rotation);
        float yRange = spr::randomFloatRange(-10.0f, 10.0f, data.randomEngine);
        spawnBloodParticle(childSpawnPosition, velocity, landingYPos + yRange, data);
    }
}

dpx::TableId spawnBloodParticle(const glm::vec3& position, const glm::vec2 velocity, float landingYPos, GameData& data)
{
    dpx::TableId textureId = *spr::findTexture("blood1"_hash, data.spr);
    glm::vec2 textureSize = {1.0f, 1.0f};
    if(spr::randomChance(0.2f, data.randomEngine))
    {
        textureId = *spr::findTexture("blood2a"_hash, data.spr);
        textureSize = {2.0f, 2.0f};
    }
    if(spr::randomChance(0.2f, data.randomEngine))
    {
        textureId = *spr::findTexture("blood2b"_hash, data.spr);
        textureSize = {2.0f, 2.0f};
    }
    spr::EntityProperties newBlood = spr::createSpriteProperties(position, {}, {}, textureSize, textureId, data.mainShader, data.mainViewport, data.worldCamera);
    newBlood["physics"_hash] = spr::Physics{velocity, glm::vec2(0.0f, 0.1f)};
    newBlood["splash_landing"_hash] = SplashLanding{landingYPos};
    return addEntity(newBlood, data);
}
