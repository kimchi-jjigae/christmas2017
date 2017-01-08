#include "tostringlist.hpp"
#include <spr/tostring/glm.hpp>

namespace spr
{
std::vector<std::string> toStringList(int32_t number)
{
    return
    {
        std::to_string(number),
    };
}

std::vector<std::string> toStringList(StringHash hash)
{
    return
    {
        hash.string,
    };
}

std::vector<std::string> toStringList(const fea::Color& color)
{
    return
    {
        std::to_string(+color.r) + " " + std::to_string(+color.g) + " " + std::to_string(+color.b) + " " + std::to_string(+color.a),
            "r: " + std::to_string(+color.r),
            "g: " + std::to_string(+color.g),
            "b: " + std::to_string(+color.b),
            "a: " + std::to_string(+color.a),
    };
}

std::vector<std::string> toStringList(const fea::Texture& texture)
{
    return
    {
        toStringList(texture.getSize())
    };
}

std::vector<std::string> toStringList(const StateExecutor& executor)
{
    return
    {
        executor.descriptor + toString(executor.condition),
    };
}

std::vector<std::string> toStringList(const CollisionExecutor& executor)
{
    return
    {
        executor.descriptor,
    };
}

std::vector<std::string> toStringList(const StateContext& stateContext)
{
    return
    {
        std::to_string(stateContext.entityId),
        std::to_string(stateContext.stateFrameCount),
    };
}

std::vector<std::string> toStringList(CollisionType type)
{
    return
    {
        type == CollisionType::Physics ? "physics" : "trigger"
    };
}

std::vector<std::string> toStringList(AABB aabb)
{
    return
    {
        toString(aabb.start) + " " + toString(aabb.size),
        "start: " + toString(aabb.start),
        "size: " + toString(aabb.size),
    };
}

std::ostream& operator<<(std::ostream& os, const StateExecutor& executor)
{
    os << executor.descriptor;
    return os;
}

std::ostream& operator<<(std::ostream& os, const CollisionExecutor& executor)
{
    os << executor.descriptor;
    return os;
}
}
