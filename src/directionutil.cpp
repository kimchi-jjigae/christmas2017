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

Direction toDirection(glm::vec2 vec)
{
    if(glm::length(vec) < 0.001f)
        return Direction::None;

    if(vec.y < 0.0f)
        return Direction::Up;
    if(vec.y > 0.0f)
        return Direction::Down;
    if(vec.x < 0.0f)
        return Direction::Left;
    if(vec.x > 0.0f)
        return Direction::Right;

    return Direction::None;
}

bool vec2ContainsDirection(glm::vec2 vec, Direction direction)
{
    if(direction == Direction::None && glm::length(vec) < 0.0001f)
        return true;
    else if(direction == Direction::Up && vec.y < -0.001f)
        return true;
    else if(direction == Direction::Down && vec.y > 0.001f)
        return true;
    else if(direction == Direction::Left && vec.x < -0.001f)
        return true;
    else if(direction == Direction::Right && vec.x > 0.001f)
        return true;

    return false;
}
