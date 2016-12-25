#include "aabb.hpp"
#include "aabbutil.hpp"

bool intersects(const AABB& a, const AABB& b)
{
    return !(a.start.x > b.start.x + b.size.x ||
             b.start.x > a.start.x + a.size.x ||
             a.start.y > b.start.y + b.size.y ||
             b.start.y > a.start.y + a.size.y);
}
