#include "entitystateslogic.hpp"
#include "../random.hpp"
#include "../stringhash.hpp"
#include "../entity/entityutil.hpp"

EntityStatesLogic::EntityStatesLogic(GameData& data):
    mData(data)
{
}

void EntityStatesLogic::update()
{
    forEach([&](int32_t id, EntityStateMachine& stateMachine)
    {
        const EntityState& state = get(stateMachine.currentState, mData.tEntityState);

        int32_t currentStateFrame = stateMachine.stateContext.stateFrameCount;

        stateMachine.stateContext.entityId = stateMachine.entityId; //a bit of a hack to set it every time, but not sure what else to do

        //call executors
        for(const Executor& executor : state.executors)
        {
            Condition condition = executor.condition;
            if(condition.type == Condition::OnStateStart && currentStateFrame == 0)
            {
                executor.function(stateMachine.stateContext, mData);
            }
            else if(condition.type == Condition::EveryNthFrame)
            {
                if((currentStateFrame - condition.everyNthFrame.offset) % condition.everyNthFrame.interval == 0)
                    executor.function(stateMachine.stateContext, mData);
            }
            else if(condition.type == Condition::FrameRandomChance)
            {
                int32_t randomVal = randomRange(0, condition.frameRandomChance.denominator - 1, mData);
                if(randomVal < condition.frameRandomChance.numerator)
                    executor.function(stateMachine.stateContext, mData);
            }
            else if(condition.type == Condition::FrameRange)
            {
                if((condition.frameRange.start == Condition::unbound || currentStateFrame >= condition.frameRange.start) &&
                   (condition.frameRange.end   == Condition::unbound || currentStateFrame <= condition.frameRange.end))
                    executor.function(stateMachine.stateContext, mData);
            }
        }

        th::Optional<StateHash> changeToState;

        if(stateMachine.stateContext.emitTransition)
        {
            auto foundState = state.transitions.find(*stateMachine.stateContext.emitTransition);
            TH_ASSERT(foundState != state.transitions.end(), "Cannot switch using nonexisting state action " << *stateMachine.stateContext.emitTransition);
            changeToState = foundState->second;
        }
        else
        {
            ++stateMachine.stateContext.stateFrameCount;

            if(stateMachine.stateContext.stateFrameCount == state.duration)
            {
                auto foundState = state.transitions.find("_next"_hash);
                TH_ASSERT(foundState != state.transitions.end(), "Duration of state reached, but action '_next' doesn't exist");
                changeToState = foundState->second;
            }
        }

        if(changeToState)
        {//state requested changed. find and setup new state

            //call any onStateEnd executors
            for(const Executor& executor : state.executors)
            {
                Condition condition = executor.condition;
                if(condition.type == Condition::OnStateEnd)
                {
                    executor.function(stateMachine.stateContext, mData);
                }
            }

            if(*changeToState == "_remove"_hash)
            {
                //it is meant to be removed, so remove it
                removeEntity(stateMachine.entityId, mData);
            }
            else
            {
                //find and setup new state
                th::Optional<int32_t> foundState;
                forEach([&] (int32_t, const EntityStateIndex& stateIndex)
                {
                    if(stateIndex.stateSet == stateMachine.currentStateSet && stateIndex.stateHash == *changeToState)
                    {
                        foundState = stateIndex.stateId;
                        return LoopResult::Break;
                    }

                    return LoopResult::Continue;
                }, mData.tEntityStateIndex);

                TH_ASSERT(foundState, "Requested state '" << changeToState->string << "' not found");

                stateMachine.stateContext = StateContext
                {
                    stateMachine.entityId,
                    0,
                    {}
                };
                stateMachine.currentState = *foundState;
            }
        }
    }, mData.tEntityStateMachine);
}
