#pragma once
#include <memory>

namespace constants
{

struct World;


struct Constants
{
    Constants() = default;
    Constants(Constants&&) = default;
    ~Constants();
    std::unique_ptr<World> world;
};

std::unique_ptr<Constants> makeConstants();
}
