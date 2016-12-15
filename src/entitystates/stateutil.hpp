#pragma once
#include "statehash.hpp"
#include <data.hpp>

TableEntry<EntityState> getEntityState(StateSetHash stateSet, StateHash state, GameData& data);
