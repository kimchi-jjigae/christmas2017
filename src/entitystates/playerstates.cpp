#include "playerstates.hpp"
#include <spr/entitystates/registerstateset.hpp>
#include <spr/entity/entityutil.hpp>
#include <spr/orientation/orientationutil.hpp>
#include <spr/random/random.hpp>
#include <spr/data/position.hpp>
#include <spr/data/entityorientation.hpp>
#include <spr/data/entitydirection.hpp>
#include <gamedata.hpp>
#include "../resources/animationutil.hpp"
#include "../spawning/spawning.hpp"

void registerPlayerStates(GameData& data)
{
    registerStateSet("player"_hash, spr::StateSet
    {
        {"idle"_hash,
            spr::EntityState
            {
                spr::indefinite,
                spr::Transitions
                {
                    { spr::StateAction("start_walk"_hash), spr::StateHash("wander"_hash) },
                },
                spr::StateExecutors
                {
                    spr::StateExecutor
                    {
                        "animation setter",
                        spr::onStateStart(),
                        [&] (spr::StateContext& context)
                        {
                            spr::setEntityFourDirectionalAnimationGroup(context.entityId, *findFourDirectionalAnimationGroup("wizard_idle"_hash, data.spr), data.spr);
                        },
                    },
                    spr::StateExecutor
                    {
                        "controls",
                        spr::everyNthFrame(1, 0),
                        [&] (spr::StateContext& context)
                        {
                            if(data.startedPlayerActions.count(PlayerAction::Staff))
                            {
                                auto spawnPosition = get(context.entityId, data.spr.t<spr::TPosition>()).coordinate;
                                auto spawnOrientation = get(context.entityId, data.spr.t<spr::TEntityOrientation>()).orientation;
                                spawnBall(spawnPosition, toDirection(spawnOrientation), data);
                            }

                            if(data.ongoingPlayerActions.count(PlayerAction::WalkUp))
                            {
                                set(context.entityId, {spr::Orientation{spr::Orientation::Up}}, data.spr.t<spr::TEntityOrientation>());
                                context.emitTransition = "start_walk"_hash;
                            }
                            else if(data.ongoingPlayerActions.count(PlayerAction::WalkDown))
                            {
                                set(context.entityId, {spr::Orientation{spr::Orientation::Down}}, data.spr.t<spr::TEntityOrientation>());
                                context.emitTransition = "start_walk"_hash;
                            }
                            else if(data.ongoingPlayerActions.count(PlayerAction::WalkLeft))
                            {
                                set(context.entityId, {spr::Orientation{spr::Orientation::Left}}, data.spr.t<spr::TEntityOrientation>());
                                context.emitTransition = "start_walk"_hash;
                            }
                            else if(data.ongoingPlayerActions.count(PlayerAction::WalkRight))
                            {
                                set(context.entityId, {spr::Orientation{spr::Orientation::Right}}, data.spr.t<spr::TEntityOrientation>());
                                context.emitTransition = "start_walk"_hash;
                            }
                        },
                    },
                },
            }
        },
        {"wander"_hash,
            spr::EntityState
            {
                spr::indefinite,
                spr::Transitions
                {
                    { spr::StateAction("_next"_hash), spr::StateHash("idle"_hash) },
                    { spr::StateAction("stop"_hash), spr::StateHash("idle"_hash) },
                },
                spr::StateExecutors
                {
                    spr::StateExecutor
                    {
                        "animation setter",
                        spr::onStateStart(),
                        [&] (spr::StateContext& context)
                        {
                            spr::setEntityFourDirectionalAnimationGroup(context.entityId, *findFourDirectionalAnimationGroup("wizard_walk"_hash, data.spr), data.spr);
                        },
                    },
                    spr::StateExecutor
                    {
                        "every frame",
                        spr::everyNthFrame(1, 0),
                        [&] (spr::StateContext& context)
                        {
                            glm::vec2& pos = get(context.entityId, data.spr.t<spr::TPosition>()).coordinate;
                            spr::Orientation oldOrientation = get(context.entityId, data.spr.t<spr::TEntityOrientation>()).orientation;

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

                                spr::Orientation currentOrientation = spr::Orientation::None;
                                if(!vec2ContainsOrientation(newDirection, oldOrientation))
                                {
                                    currentOrientation = spr::toOrientation(newDirection);
                                    set(context.entityId, spr::EntityOrientation{currentOrientation}, data.spr.t<spr::TEntityOrientation>());
                                }
                                else
                                {
                                    currentOrientation = oldOrientation;
                                }

                                pos += newDirection * 3.5f;
                                set(context.entityId, {newDirection}, data.spr.t<spr::TEntityDirection>());
                            }
                            else
                            {
                                context.emitTransition = "stop"_hash;
                            }

                            if(data.startedPlayerActions.count(PlayerAction::Staff))
                            {
                                auto spawnPosition = get(context.entityId, data.spr.t<spr::TPosition>()).coordinate;

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
    }, data.spr);
}
