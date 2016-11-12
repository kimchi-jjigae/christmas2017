#pragma once
#include <fea/rendering/color.hpp>
#include <vector>
#include <string>
#include <sstream>
#include <glm.hpp>

std::vector<std::string> toStringList(int32_t number);

template<typename Vec2Type>
std::vector<std::string> toStringList(const glm::tvec2<Vec2Type>& vec2)
{
    return
    {
        std::to_string(vec2.x) + " " + std::to_string(vec2.y),
            "x: " + std::to_string(vec2.x),
            "y: " + std::to_string(vec2.y),
    };
}

template<typename T>
std::vector<std::string> toStringList(const std::vector<T>& list)
{
    std::vector<std::string> result;

    std::stringstream total;

    for(const auto& item : list)
    {
        std::stringstream ss;
        ss << item;
        total << item << ", ";
        result.push_back(ss.str());
    }

    std::string totalString = total.str();

    if(!list.empty())
    {
        totalString.pop_back();
        totalString.pop_back();
    }

    result.insert(result.begin(), totalString);
    return result;
}

std::vector<std::string> toStringList(const fea::Color& color);
