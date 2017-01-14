#pragma once
#include <fea/rendering/color.hpp>
#include <fea/rendering/texture.hpp>
#include <fea/rendering/viewport.hpp>
#include <vector>
#include <string>
#include <sstream>
#include <spr/glm.hpp>
#include <spr/entitystates/stateexecutor.hpp>
#include <spr/physics/collisiontype.hpp>
#include <spr/physics/collisionexecutor.hpp>
#include <spr/physics/aabb.hpp>
#include <spr/rendering/renderpass.hpp>

namespace spr
{
std::vector<std::string> toStringList(int32_t number);
std::vector<std::string> toStringList(StringHash hash);

std::vector<std::string> toStringList(const fea::Color& color);
std::vector<std::string> toStringList(const fea::Texture& texture);
std::vector<std::string> toStringList(const StateExecutor& executor);
std::vector<std::string> toStringList(const CollisionExecutor& executor);
std::vector<std::string> toStringList(const StateContext& stateContext);
std::vector<std::string> toStringList(const fea::Viewport& viewport);
std::vector<std::string> toStringList(const RenderPass& renderPass);

std::vector<std::string> toStringList(CollisionType type);
std::vector<std::string> toStringList(AABB aabb);

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

template<typename T>
std::vector<std::string> toStringList(const std::shared_ptr<T>& ptr)
{
    if(ptr)
    {
        return toStringList(*ptr);
    }
    else
    {
        return {"nullptr"};
    }
}

template<typename Key, typename Value>
std::vector<std::string> toStringList(const std::unordered_map<Key, Value>& map)
{
    std::vector<std::string> result;

    std::stringstream total;

    for(auto iter : map)
    {
        std::stringstream ss;
        ss << iter.first << "->" << iter.second;
        total << ss.str() << ", ";
        result.push_back(ss.str());
    }

    std::string totalString = total.str();

    if(!map.empty())
    {
        totalString.pop_back();
        totalString.pop_back();
    }

    result.insert(result.begin(), totalString);
    return result;
}

std::ostream& operator<<(std::ostream& os, const StateExecutor& executor);
std::ostream& operator<<(std::ostream& os, const CollisionExecutor& executor);
}
