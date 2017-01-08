#pragma once
#include <unordered_map>
#include "statehash.hpp"

namespace spr
{
using Transitions = std::unordered_map<StateAction,StateHash>;
}
