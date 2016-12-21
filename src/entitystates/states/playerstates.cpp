#include "playerstates.hpp"
#include "registerstateset.hpp"

void registerPlayerStates(GameData& gameData)
{
    //states for a typical mario 2d platform character
    registerStateSet("player"_hash, StateSet
    {
        //our run state, which is when the player holds the run button while mario is moving
        {"idle"_hash,
            EntityState
            {
                //duration of the state
                Duration(600),
                //state actions that lead to transitioning to another state
                Transitions
                {
                    { StateAction("_next"_hash), StateHash("poop"_hash) },
                    //{ StateAction("slow_down"_hash), StateHash("walk"_hash) },
                    //{ StateAction("turn"_hash), StateHash("turn_slide"_hash) },
                    //{ StateAction("jump"_hash), StateHash("jump"_hash) },
                },
                //any state can have zero or more executors
                Executors
                {
                    Executor
                    {
                        "on start printer",
                        onStateStart(),
                        [] (StateContext& context, GameData& data)
                        {
                            std::cout << "on start\n";
                        },
                    },
                    Executor
                    {
                        "every frame printer",
                        everyNthFrame(10, 100),
                        [] (StateContext& context, GameData& data)
                        {
                            std::cout << "nth frame\n";
                            glm::vec2& pos = get(context.entityId, data.tPosition).coordinate;
                            pos.x += 4.0f;
                        },
                    },
                    //standard sprite animation manipulating executor that plays run animation
                    //spriteAnimateExecutor({0, 36}, {12, 14}, 3, 10, Animation::Loop),
                },
            }
        },
        {"poop"_hash,
            EntityState
            {
                //duration of the state
                indefinite,
                //state actions that lead to transitioning to another state
                Transitions
                {
                    { StateAction("blapp"_hash), StateHash("idle"_hash) },
                    //{ StateAction("slow_down"_hash), StateHash("walk"_hash) },
                    //{ StateAction("turn"_hash), StateHash("turn_slide"_hash) },
                    //{ StateAction("jump"_hash), StateHash("jump"_hash) },
                },
                //any state can have zero or more executors
                Executors
                {
                    Executor
                    {
                        "on start printer",
                        onStateStart(),
                        [] (StateContext& context, GameData& data)
                        {
                            std::cout << "on POOP\n";
                        },
                    },
                    Executor
                    {
                        "every frame printer",
                        everyNthFrame(10, 100),
                        [] (StateContext& context, GameData& data)
                        {
                            std::cout << "nth POOP\n";
                            context.emitTransition = "blapp"_hash;
                        },
                    },
                    //standard sprite animation manipulating executor that plays run animation
                    //spriteAnimateExecutor({0, 36}, {12, 14}, 3, 10, Animation::Loop),
                },
            }
        },
        //our jump state, which is after the player pressed jump when being on ground
        //{"jump"_hash,
        //    EntityState
        //    {
        //        //duration of the state
        //        Duration(60),
        //        //state actions that lead to transitioning to another state
        //        Transitions
        //        {
        //            { StateAction("_next"_hash), StateHash("fall"_hash) },
        //            { StateAction("stop"_hash), StateHash("fall"_hash) },
        //        },
        //        //any state can have zero or more executors
        //        Executors
        //        {
        //            //this executor makes us go upwards and excerts some air control
        //            Executor
        //            {
        //                "movement_controller",
        //                everyNthFrame(1, 0),
        //                [] (StateContext& context, GameData& data)
        //                {
        //                    //int32_t objectId = context.entityId;

        //                    //glm::vec2& velocity = get(objectId, data.tVelocity);
        //                    //velocity.y = -5.0f;
        //                    //velocity.x = get(objectId, data.tDirections);
        //                },
        //            },
        //            //this executor makes sure we can stop falling
        //            Executor
        //            {
        //                //condition
        //                "fall_timer",
        //                everyNthFrame(1, 0),
        //                [] (StateContext& context, GameData& data)
        //                {
        //                    //PlayerAction currentAction = data.currentPlayerAction;

        //                    //if(currentAction != Action::Jump)
        //                    //    context.emitTransition = "stop"_hash;
        //                },
        //            },
        //            //standard sprite animation manipulating executor that plays run animation
        //            //spriteAnimateExecutor({0, 36}, {12, 14}, 3, 10, Animation::ForwardStop),
        //        },
        //    }
        //},
    }, gameData);
}
