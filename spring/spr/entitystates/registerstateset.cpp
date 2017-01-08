#include "registerstateset.hpp"
#include <spr/data/entitystateindex.hpp>

namespace spr
{
void registerStateSet(StateHash setHash, StateSet set, TableModule& tables)
{
    for(auto& stateIter : set)
    {
        int32_t newSet = insert(std::move(stateIter.second), tables.t<TEntityState>()).id;

        EntityStateIndex index
        {
            setHash,
            stateIter.first,
            newSet
        };

        insert(index, tables.t<TEntityStateIndex>());
    }
}
}
