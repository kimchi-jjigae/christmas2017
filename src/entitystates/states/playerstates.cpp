#include "playerstates.hpp"
#include "registerstateset.hpp"
#include "../../entity/entityutil.hpp"
#include "../../resources/animationutil.hpp"
#include "../../directionutil.hpp"
#include "../../random.hpp"

void registerPlayerStates(GameData& gameData)
{
    registerStateSet("player"_hash, StateSet
    {
        {"idle"_hash,
            EntityState
            {
                indefinite,
                Transitions
                {
                    { StateAction("start_walk"_hash), StateHash("wander"_hash) },
                },
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
                            if(data.startedPlayerActions.count(PlayerAction::WalkUp))
                            {
                                set(context.entityId, Orientation{Direction::Up}, data.tOrientation);
                                context.emitTransition = "start_walk"_hash;
                            }
                            else if(data.startedPlayerActions.count(PlayerAction::WalkDown))
                            {
                                set(context.entityId, Orientation{Direction::Down}, data.tOrientation);
                                context.emitTransition = "start_walk"_hash;
                            }
                            else if(data.startedPlayerActions.count(PlayerAction::WalkLeft))
                            {
                                set(context.entityId, Orientation{Direction::Left}, data.tOrientation);
                                context.emitTransition = "start_walk"_hash;
                            }
                            else if(data.startedPlayerActions.count(PlayerAction::WalkRight))
                            {
                                set(context.entityId, Orientation{Direction::Right}, data.tOrientation);
                                context.emitTransition = "start_walk"_hash;
                            }
                        },
                    },
                },
            }
        },
        {"wander"_hash,
            EntityState
            {
                indefinite,
                Transitions
                {
                    { StateAction("_next"_hash), StateHash("idle"_hash) },
                    { StateAction("stop"_hash), StateHash("idle"_hash) },
                },
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
                        everyNthFrame(1, 0),
                        [] (StateContext& context, GameData& data)
                        {
                            glm::vec2& pos = get(context.entityId, data.tPosition).coordinate;
                            glm::vec2 direction;

                            bool moves = false;

                            if(data.ongoingPlayerActions.count(PlayerAction::WalkLeft) != 0)
                            {
                                direction.x -= 1.0f;
                                moves = true;
                            }
                            if(data.ongoingPlayerActions.count(PlayerAction::WalkRight) != 0)
                            {
                                direction.x += 1.0f;
                                moves = true;
                            }
                            if(data.ongoingPlayerActions.count(PlayerAction::WalkUp) != 0)
                            {
                                direction.y -= 1.0f;
                                moves = true;
                            }
                            if(data.ongoingPlayerActions.count(PlayerAction::WalkDown) != 0)
                            {
                                direction.y += 1.0f;
                                moves = true;
                            }

                            Direction currentDir = toDirection(direction);

                            pos += direction * 3.5f;

                            if(!moves)
                            {
                                context.emitTransition = "stop"_hash;
                            }
                            else
                            {
                                if(currentDir != Direction::None)
                                    set(context.entityId, {currentDir}, data.tOrientation);
                            }
                        },
                    },
                },
            }
        },
    }, gameData);
}
