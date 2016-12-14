#pragma once
#include "statecontext.hpp"
#include "condition.hpp"

struct GameData;

using ExecutorFunction = void (*)(StateContext&, GameData&);

struct Executor
{
    const char* descriptor;
    Condition condition;
    ExecutorFunction function;
};

using Executors = std::vector<Executor>;
