#pragma once
#include "statecontext.hpp"
#include "condition.hpp"

struct GameData;

using ExecutorFunction = void (*)(StateContext&, GameData&);

struct Executor
{
    Condition condition;
    ExecutorFunction function;
};
