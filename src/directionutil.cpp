#include "directionutil.hpp"

glm::vec2 toVec2(Direction direction)
{
    if(direction == Direction::Up)
        return {0.0f, -1.0f};
    else if(direction == Direction::Down)
        return {0.0f, 1.0f};
    else if(direction == Direction::Left)
        return {-1.0f, 0.0f};
    else if(direction == Direction::Right)
        return {1.0f, 0.0f};
    else
        return {0.0f, 0.0f};
}
