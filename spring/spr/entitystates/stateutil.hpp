#pragma once
#include "statehash.hpp"
#include <dpx/tables.hpp>
#include <spr/data/entitystate.hpp>
#include <spr/tables/tablemodule.hpp>

namespace spr
{
dpx::TableEntry<EntityState> getEntityState(StateSetHash stateSet, StateHash state, TableModule& tables);
}
