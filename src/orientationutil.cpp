#include "orientationutil.hpp"

glm::vec2 toDirection(Orientation orientation)
{
    if(orientation == Orientation::Up)
        return {0.0f, -1.0f};
    else if(orientation == Orientation::Down)
        return {0.0f, 1.0f};
    else if(orientation == Orientation::Left)
        return {-1.0f, 0.0f};
    else if(orientation == Orientation::Right)
        return {1.0f, 0.0f};
    else
        return {0.0f, 0.0f};
}

Orientation toOrientation(glm::vec2 vec)
{
    if(glm::length(vec) < 0.001f)
        return Orientation::None;

    if(vec.y < 0.0f)
        return Orientation::Up;
    if(vec.y > 0.0f)
        return Orientation::Down;
    if(vec.x < 0.0f)
        return Orientation::Left;
    if(vec.x > 0.0f)
        return Orientation::Right;

    return Orientation::None;
}

bool vec2ContainsOrientation(glm::vec2 vec, Orientation orientation)
{
    if(orientation == Orientation::None && glm::length(vec) < 0.0001f)
        return true;
    else if(orientation == Orientation::Up && vec.y < -0.001f)
        return true;
    else if(orientation == Orientation::Down && vec.y > 0.001f)
        return true;
    else if(orientation == Orientation::Left && vec.x < -0.001f)
        return true;
    else if(orientation == Orientation::Right && vec.x > 0.001f)
        return true;

    return false;
}
