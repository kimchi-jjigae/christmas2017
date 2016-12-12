//states for a typical mario 2d platform character
"mario"_hash, StateSet
{
    //our run state, which is when the player holds the run button while mario is moving
    {"run"_hash,
        State
        {
            //duration of the state
            indefinite(),
            //state actions that lead to transitioning to another state
            Transitions
            {
                { StateAction("stop"_hash), StateHash("idle"_hash) },
                { StateAction("slow_down"_hash), StateHash("walk"_hash) },
                { StateAction("turn"_hash), StateHash("turn_slide"_hash) },
                { StateAction("jump"_hash), StateHash("jump"_hash) },
            },
            //any state can have zero or more executors
            Executors
            {
                //this executor stores the direction we run in as a first step
                Executor
                {
                    //condition
                    onStateStart(),
                    [] (StateContext& context, GameData& data)
                    {
                        int32_t objectId = context.objectId;
                        int32_t initialDirection =  get(objectId, data.tDirection);
                        RunState& runState = get(objectId, data.tRunState);
                        runState.initialDirection = direction;
                    },
                }
                //this executor propells mario
                Executor
                {
                    //condition
                    everyNthFrame(1),
                    [] (StateContext& context, GameData& data)
                    {
                        int32_t objectId = context.objectId;
                        
                        int32_t direction = get(objectId, data.tDirections);

                        glm::vec2& velocity = get(objectId, data.tVelocity);
                        velocity += 5.0f * direction;
                    },
                },
                //this executor makes sure we can change states on input
                Executor
                {
                    //condition
                    everyNthFrame(1),
                    [] (StateContext& context, GameData& data)
                    {
                        PlayerAction currentAction = data.currentPlayerAction;

                        if(currentAction == Action::Jump)
                            context.emitTransition = "jump"_hash;
                        else if(currentAction == Action::Walk)
                            context.emitTransition = "slow_down"_hash;
                        else if(currentAction == Action::Idle)
                            context.emitTransition = "stop"_hash;

                        int32_t currentDirection = get(objectId, data.tDirections);
                        RunState& runState = get(objectId, data.tRunState);
                        int32_t initialDirection = runState.initialDirection;

                        if(currentAction != initialDirection)
                            context.emitTransition = "turn"_hash;
                    },
                },
                //standard sprite animation manipulating executor that plays run animation
                spriteAnimateExecutor({0, 36}, {12, 14}, 3, 10, Animation::Loop),
            },
        }
    },
    //our jump state, which is after the player pressed jump when being on ground
    {"jump"_hash,
        State
        {
            //duration of the state
            timed(60, "fall"_hash),
            //state actions that lead to transitioning to another state
            Transitions
            {
                { StateAction("stop"_hash), State("fall"_hash) },
            },
            //any state can have zero or more executors
            Executors
            {
                //this executor makes us go upwards and excerts some air control
                Executor
                {
                    //condition
                    everyNthFrame(1),
                    [] (StateContext& context, GameData& data)
                    {
                        int32_t objectId = context.objectId;
                        
                        glm::vec2& velocity = get(objectId, data.tVelocity);
                        velocity.y = -5.0f;
                        velocity.x = get(objectId, data.tDirections);
                    },
                },
                //this executor makes sure we can stop falling
                Executor
                {
                    //condition
                    everyNthFrame(1),
                    [] (StateContext& context, GameData& data)
                    {
                        PlayerAction currentAction = data.currentPlayerAction;

                        if(currentAction != Action::Jump)
                            context.emitTransition = "fall"_hash;
                    },
                },
                //standard sprite animation manipulating executor that plays run animation
                spriteAnimateExecutor({0, 36}, {12, 14}, 3, 10, Animation::ForwardStop),
            },
        }
    },
    /*
    .
    .
    .
    */
}
