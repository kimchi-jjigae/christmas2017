#include "registerstateset.hpp"
#include <spr/data/entitystateindex.hpp>

namespace spr
{
void registerStateSet(StateHash setHash, StateSet set, Tables& tables)
{
    for(auto& stateIter : set)
    {
        int32_t newSet = insert(std::move(stateIter.second), *tables.tEntityState).id;

        EntityStateIndex index
        {
            setHash,
            stateIter.first,
            newSet
        };

        insert(index, *tables.tEntityStateIndex);
    }
}
}
