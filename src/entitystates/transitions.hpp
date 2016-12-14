#pragma once
#include <unordered_map>
#include "statehash.hpp"

using Transitions = std::unordered_map<StateAction,StateHash>;
