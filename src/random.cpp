#include "random.hpp"
#include <data.hpp>

int32_t randomRange(int32_t low, int32_t high, GameData& data)
{
    TH_ASSERT(false, "Implement me");
    return -1;
}

Direction randomDirection(GameData& data)
{
    int32_t r = rand() % 4; //bad random!

    if(r == 0)
        return Direction::Up;
    else if(r == 1)
        return Direction::Down;
    else if(r == 2)
        return Direction::Left;
    else if(r == 3)
        return Direction::Right;
    else
        return Direction::None;
}
