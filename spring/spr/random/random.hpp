#pragma once
#include <thero/assert.hpp>
#include <cstdint>
#include <spr/orientation/orientation.hpp>

struct GameData;

namespace spr
{
template <typename RandomEngine>
int32_t randomRange(int32_t low, int32_t high, RandomEngine& randomEngine)
{
    TH_ASSERT(false, "Implement me");
    return -1;
}

template <typename RandomEngine>
Orientation randomOrientation(RandomEngine& randomEngine)
{
    int32_t r = rand() % 4; //bad random!

    if(r == 0)
        return Orientation::Up;
    else if(r == 1)
        return Orientation::Down;
    else if(r == 2)
        return Orientation::Left;
    else if(r == 3)
        return Orientation::Right;
    else
        return Orientation::None;
}
}
