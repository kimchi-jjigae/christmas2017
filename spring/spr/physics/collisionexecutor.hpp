#pragma once
#include <functional>
#include "collisioncontext.hpp"

namespace spr
{
using CollisionExecutorFunction = std::function<void(const CollisionContext&)>;

struct CollisionExecutor
{
    const char* descriptor;
    CollisionExecutorFunction function;
};

using CollisionExecutors = std::vector<CollisionExecutor>;
}
