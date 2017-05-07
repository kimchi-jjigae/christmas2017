#include "entityproperties.hpp"

void applyOverrides(const EntityProperties& overrides, EntityProperties& target)
{
    for(auto overrideIter : overrides)
    {
        target[overrideIter.first] = overrideIter.second;
    }
}
