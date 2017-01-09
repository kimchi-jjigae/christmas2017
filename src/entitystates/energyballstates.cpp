#include "energyballstates.hpp"
#include <spr/entitystates/registerstateset.hpp>
#include <spr/orientation/orientationutil.hpp>
#include <spr/data/entitydirection.hpp>
#include <spr/data/position.hpp>
#include <gamedata.hpp>

void registerEnergyBallStates(GameData& data)
{
    registerStateSet("energy_ball"_hash, spr::StateSet
    {
        {"travel"_hash,
            spr::EntityState
            {
                spr::Duration(60),
                spr::Transitions
                {
                    { spr::StateAction("_next"_hash), spr::StateHash("_remove"_hash) },
                },
                spr::StateExecutors
                {
                    spr::StateExecutor
                    {
                        "propeller",
                        spr::everyNthFrame(1, 0),
                        [&] (spr::StateContext& context)
                        {
                            glm::vec2 direction = get(context.entityId, *data.spr.tEntityDirection).direction;
                            glm::vec2& position = get(context.entityId, *data.spr.tPosition).coordinate;
                            position += direction * 8.0f;
                        },
                    },
                },
            }
        },
    }, data.spr);
}
