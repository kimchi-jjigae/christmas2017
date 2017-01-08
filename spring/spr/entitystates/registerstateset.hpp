#pragma once
#include "stateset.hpp"
#include "transitions.hpp"
#include "stateexecutor.hpp"
#include <spr/hash/stringhash.hpp>
#include <spr/tables/tablemodule.hpp>

namespace spr
{
void registerStateSet(StateHash setHash, StateSet set, TableModule& tables);
}
