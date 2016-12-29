#pragma once
#include "collisioncontext.hpp"

struct GameData;

using CollisionExecutorFunction = void (*)(CollisionContext&, GameData&);

struct CollisionExecutor
{
    const char* descriptor;
    CollisionExecutorFunction function;
};

using CollisionExecutors = std::vector<CollisionExecutor>;
