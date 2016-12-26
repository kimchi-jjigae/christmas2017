#include "slimestates.hpp"
#include "registerstateset.hpp"
#include "../../directionutil.hpp"

void registerSlimeStates(GameData& gameData)
{
    registerStateSet("slime"_hash, StateSet
    {
        {"engage"_hash,
            EntityState
            {
                indefinite,
                Transitions
                {
                    //{ StateAction("_next"_hash), StateHash("_remove"_hash) },
                },
                Executors
                {
                    Executor
                    {
                        "engage_mover",
                        everyNthFrame(1, 0),
                        [] (StateContext& context, GameData& data)
                        {
                            auto targetPos = get(data.playerId, data.tPosition).coordinate;
                            targetPos += glm::diskRand(400.0f);
                            glm::vec2& position = get(context.entityId, data.tPosition).coordinate;
                            auto direction = glm::normalize(targetPos - position + glm::vec2(0.00001f, 0.0f));
                            position += direction * 1.0f;
                        },
                    },
                },
            }
        },
    }, gameData);
}
