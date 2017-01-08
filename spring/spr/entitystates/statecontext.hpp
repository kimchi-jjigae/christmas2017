#pragma once
#include <cstdint>
#include <thero/optional.hpp>
#include "statehash.hpp"

namespace spr
{
struct StateContext
{
    int32_t entityId;
    int32_t stateFrameCount;
    th::Optional<StateAction> emitTransition;
};
}
