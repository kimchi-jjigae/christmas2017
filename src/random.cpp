#include "random.hpp"
#include <data.hpp>

int32_t randomRange(int32_t low, int32_t high, GameData& data)
{
    TH_ASSERT(false, "Implement me");
    return -1;
}

Orientation randomOrientation(GameData& data)
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
