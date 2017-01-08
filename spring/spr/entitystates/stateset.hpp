#pragma once
#include "statehash.hpp"
#include <unordered_map>
#include <spr/data/entitystate.hpp>

namespace spr
{
using StateSet = std::unordered_map<StateHash, EntityState>;
}
