#include "stateutil.hpp"
#include <spr/data/entitystateindex.hpp>

namespace spr
{
dpx::TableEntry<EntityState> getEntityState(StateSetHash stateSet, StateHash state, TableModule& tables)
{
    auto found = findOne([&](int32_t id, const EntityStateIndex& stateIndex)
    {
        return stateIndex.stateSet == stateSet && stateIndex.stateHash == state;
    }, tables.t<TEntityStateIndex>());

    TH_ASSERT(found, "could not find given state " << state.string << " in set " << stateSet.string << "\n");

    return {found->id, get(found->id, tables.t<TEntityState>())};
}
}
