#include "stateutil.hpp"
#include <data.hpp>

dpx::TableEntry<EntityState> getEntityState(StateSetHash stateSet, StateHash state, GameData& data)
{
    auto found = findOne([&](int32_t id, const EntityStateIndex& stateIndex)
    {
        return stateIndex.stateSet == stateSet && stateIndex.stateHash == state;
    }, data.tEntityStateIndex);

    TH_ASSERT(found, "could not find given state " << state.string << " in set " << stateSet.string << "\n");

    return {found->id, get(found->id, data.tEntityState)};
}
