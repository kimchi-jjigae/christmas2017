#include "energyballstates.hpp"
#include "registerstateset.hpp"
#include "../../directionutil.hpp"

void registerEnergyBallStates(GameData& gameData)
{
    registerStateSet("energy_ball"_hash, StateSet
    {
        {"travel"_hash,
            EntityState
            {
                Duration(60),
                Transitions
                {
                    { StateAction("_next"_hash), StateHash("_remove"_hash) },
                },
                Executors
                {
                    Executor
                    {
                        "propeller",
                        everyNthFrame(1, 0),
                        [] (StateContext& context, GameData& data)
                        {
                            Direction spawnOrientation = get(context.entityId, data.tOrientation).direction;
                            glm::vec2 direction = toVec2(spawnOrientation);
                            glm::vec2& position = get(context.entityId, data.tPosition).coordinate;
                            position += direction * 8.0f;
                        },
                    },
                },
            }
        },
    }, gameData);
}
