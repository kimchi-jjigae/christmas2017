#include "energyballstates.hpp"
#include "registerstateset.hpp"
#include "../../orientationutil.hpp"

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
                StateExecutors
                {
                    StateExecutor
                    {
                        "propeller",
                        everyNthFrame(1, 0),
                        [] (StateContext& context, GameData& data)
                        {
                            glm::vec2 direction = get(context.entityId, data.tEntityDirection).direction;
                            glm::vec2& position = get(context.entityId, data.tPosition).coordinate;
                            position += direction * 8.0f;
                        },
                    },
                },
            }
        },
    }, gameData);
}
