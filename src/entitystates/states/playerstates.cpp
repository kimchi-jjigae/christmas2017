#include "playerstates.hpp"
#include "registerstateset.hpp"
#include "../../entity/entityutil.hpp"
#include "../../resources/animationutil.hpp"
#include "../../directionutil.hpp"
#include "../../random.hpp"

void registerPlayerStates(GameData& gameData)
{
    //states for a typical mario 2d platform character
    registerStateSet("player"_hash, StateSet
    {
        {"idle"_hash,
            EntityState
            {
                //duration of the state
                indefinite,
                //state actions that lead to transitioning to another state
                Transitions
                {
                    { StateAction("bored"_hash), StateHash("wander"_hash) },
                },
                //any state can have zero or more executors
                Executors
                {
                    Executor
                    {
                        "animation setter",
                        onStateStart(),
                        [] (StateContext& context, GameData& data)
                        {
                            setEntityFourDirectionalAnimationGroup(context.entityId, *findFourDirectionalAnimationGroup("wizard_idle"_hash, data), data);
                        },
                    },
                    Executor
                    {
                        "every frame printer",
                        everyNthFrame(1, 0),
                        [] (StateContext& context, GameData& data)
                        {
                            if(context.stateFrameCount > 300)
                                context.emitTransition = "bored"_hash;
                        },
                    },
                },
            }
        },
        //our run state, which is when the player holds the run button while mario is moving
        {"wander"_hash,
            EntityState
            {
                //duration of the state
                Duration(600),
                //state actions that lead to transitioning to another state
                Transitions
                {
                    { StateAction("_next"_hash), StateHash("idle"_hash) },
                },
                //any state can have zero or more executors
                Executors
                {
                    Executor
                    {
                        "animation setter",
                        onStateStart(),
                        [] (StateContext& context, GameData& data)
                        {
                            setEntityFourDirectionalAnimationGroup(context.entityId, *findFourDirectionalAnimationGroup("wizard_walk"_hash, data), data);
                        },
                    },
                    Executor
                    {
                        "every frame",
                        everyNthFrame(10, 100),
                        [] (StateContext& context, GameData& data)
                        {
                            glm::vec2& pos = get(context.entityId, data.tPosition).coordinate;

                            Direction currentDir = get(context.entityId, data.tOrientation).direction;

                            pos += 4.0f * toVec2(currentDir);

                            if(rand() % 10 == 0)
                            {
                                Direction randomDir = randomDirection(data);
                                set(context.entityId, Orientation{randomDir}, data.tOrientation);
                            }
                        },
                    },
                },
            }
        },
    }, gameData);
}
