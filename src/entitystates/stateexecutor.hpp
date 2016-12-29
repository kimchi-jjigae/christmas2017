#pragma once
#include "statecontext.hpp"
#include "condition.hpp"

struct GameData;

using StateExecutorFunction = void (*)(StateContext&, GameData&);

struct StateExecutor
{
    const char* descriptor;
    Condition condition;
    StateExecutorFunction function;
};

using StateExecutors = std::vector<StateExecutor>;
