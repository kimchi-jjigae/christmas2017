#include "tostringlist.hpp"

std::vector<std::string> toStringList(int32_t number)
{
    return
    {
        std::to_string(number),
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
