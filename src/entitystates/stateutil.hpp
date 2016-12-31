#pragma once
#include "statehash.hpp"
#include <data.hpp>

dpx::TableEntry<EntityState> getEntityState(StateSetHash stateSet, StateHash state, GameData& data);
