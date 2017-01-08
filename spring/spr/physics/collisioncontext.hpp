#pragma once
#include <cstdint>

namespace spr
{
struct CollisionContext
{
    int32_t entityId;
    int32_t collidedWithId;
};
}
