#pragma once
#include "../stateset.hpp"
#include "../transitions.hpp"
#include "../../stringhash.hpp"
#include "../stateexecutor.hpp"

struct GameData;

void registerStateSet(StateHash setHash, StateSet set, GameData& data);
