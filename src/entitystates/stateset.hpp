#pragma once
#include "statehash.hpp"
#include <unordered_map>
#include <data.hpp>
using StateSet = std::unordered_map<StateHash, EntityState>;
