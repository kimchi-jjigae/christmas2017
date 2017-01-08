#pragma once
#include "statecontext.hpp"
#include "condition.hpp"
#include <functional>

namespace spr
{
struct StateExecutor
{
    using StateExecutorFunction = std::function<void(StateContext&)>;

    const char* descriptor;
    Condition condition;
    StateExecutorFunction function;
};

using StateExecutors = std::vector<StateExecutor>;
}
