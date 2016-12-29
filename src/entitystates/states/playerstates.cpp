#include "playerstates.hpp"
#include "registerstateset.hpp"
#include "../../entity/entityutil.hpp"
#include "../../resources/animationutil.hpp"
#include "../../orientationutil.hpp"
#include "../../spawning/spawning.hpp"
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
                StateExecutors
                {
                    StateExecutor
                    {
                        "animation setter",
                        onStateStart(),
                        [] (StateContext& context, GameData& data)
                        {
                            setEntityFourDirectionalAnimationGroup(context.entityId, *findFourDirectionalAnimationGroup("wizard_idle"_hash, data), data);
                        },
                    },
                    StateExecutor
                    {
                        "controls",
                        everyNthFrame(1, 0),
                        [] (StateContext& context, GameData& data)
                        {
                            if(data.startedPlayerActions.count(PlayerAction::Staff))
                            {
                                auto spawnPosition = get(context.entityId, data.tPosition).coordinate;
                                auto spawnOrientation = get(context.entityId, data.tEntityOrientation).orientation;
                                spawnBall(spawnPosition, toDirection(spawnOrientation), data);
                            }

                            if(data.ongoingPlayerActions.count(PlayerAction::WalkUp))
                            {
                                set(context.entityId, {Orientation{Orientation::Up}}, data.tEntityOrientation);
                                context.emitTransition = "start_walk"_hash;
                            }
                            else if(data.ongoingPlayerActions.count(PlayerAction::WalkDown))
                            {
                                set(context.entityId, {Orientation{Orientation::Down}}, data.tEntityOrientation);
                                context.emitTransition = "start_walk"_hash;
                            }
                            else if(data.ongoingPlayerActions.count(PlayerAction::WalkLeft))
                            {
                                set(context.entityId, {Orientation{Orientation::Left}}, data.tEntityOrientation);
                                context.emitTransition = "start_walk"_hash;
                            }
                            else if(data.ongoingPlayerActions.count(PlayerAction::WalkRight))
                            {
                                set(context.entityId, {Orientation{Orientation::Right}}, data.tEntityOrientation);
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
                StateExecutors
                {
                    StateExecutor
                    {
                        "animation setter",
                        onStateStart(),
                        [] (StateContext& context, GameData& data)
                        {
                            setEntityFourDirectionalAnimationGroup(context.entityId, *findFourDirectionalAnimationGroup("wizard_walk"_hash, data), data);
                        },
                    },
                    StateExecutor
                    {
                        "every frame",
                        everyNthFrame(1, 0),
                        [] (StateContext& context, GameData& data)
                        {
                            glm::vec2& pos = get(context.entityId, data.tPosition).coordinate;
                            Orientation oldOrientation = get(context.entityId, data.tEntityOrientation).orientation;

                            glm::vec2 newDirection;

                            if(data.ongoingPlayerActions.count(PlayerAction::WalkLeft) != 0)
                            {
                                newDirection.x -= 1.0f;
                            }
                            if(data.ongoingPlayerActions.count(PlayerAction::WalkRight) != 0)
                            {
                                newDirection.x += 1.0f;
                            }
                            if(data.ongoingPlayerActions.count(PlayerAction::WalkUp) != 0)
                            {
                                newDirection.y -= 1.0f;
                            }
                            if(data.ongoingPlayerActions.count(PlayerAction::WalkDown) != 0)
                            {
                                newDirection.y += 1.0f;
                            }

                            if(glm::length(newDirection) > 0.0f)
                            {
                                newDirection = glm::normalize(newDirection);

                                Orientation currentOrientation = Orientation::None;
                                if(!vec2ContainsOrientation(newDirection, oldOrientation))
                                {
                                    currentOrientation = toOrientation(newDirection);
                                    set(context.entityId, EntityOrientation{currentOrientation}, data.tEntityOrientation);
                                }
                                else
                                {
                                    currentOrientation = oldOrientation;
                                }

                                pos += newDirection * 3.5f;
                                set(context.entityId, {newDirection}, data.tEntityDirection);
                            }
                            else
                            {
                                context.emitTransition = "stop"_hash;
                            }

                            if(data.startedPlayerActions.count(PlayerAction::Staff))
                            {
                                auto spawnPosition = get(context.entityId, data.tPosition).coordinate;

                                if(glm::length(newDirection) > 0.0f)
                                    spawnBall(spawnPosition, newDirection, data);
                                else
                                    spawnBall(spawnPosition, toDirection(oldOrientation), data);
                            }
                        },
                    },
                },
            }
        },
    }, gameData);
}
