#include "registerstateset.hpp"

void registerStateSet(StateHash setHash, StateSet set, GameData& data)
{
    for(auto& stateIter : set)
    {
        int32_t newSet = insert(std::move(stateIter.second), data.tEntityState).id;

        EntityStateIndex index
        {
            setHash,
            stateIter.first,
            newSet
        };

        insert(index, data.tEntityStateIndex);
    }
}
