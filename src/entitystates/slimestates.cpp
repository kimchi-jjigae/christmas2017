#include "slimestates.hpp"
#include <spr/entitystates/registerstateset.hpp>
#include <spr/orientation/orientationutil.hpp>
#include <spr/data/position.hpp>
#include <gamedata.hpp>

void registerSlimeStates(GameData& data)
{
    spr::registerStateSet("slime"_hash, spr::StateSet
    {
        {"engage"_hash,
            spr::EntityState
            {
                spr::indefinite,
                spr::Transitions
                {
                    //{ StateAction("_next"_hash), StateHash("_remove"_hash) },
                },
                spr::StateExecutors
                {
                    spr::StateExecutor
                    {
                        "engage_mover",
                        spr::everyNthFrame(1, 0),
                        [&] (spr::StateContext& context)
                        {
                            auto targetPos = get(data.playerId, *data.spr.tPosition).coordinate;
                            targetPos += glm::diskRand(400.0f);
                            glm::vec2& position = get(context.entityId, *data.spr.tPosition).coordinate;
                            auto direction = glm::normalize(targetPos - position + glm::vec2(0.00001f, 0.0f));
                            position += direction * 1.0f;
                        },
                    },
                },
            }
        },
    }, data.spr);
}
