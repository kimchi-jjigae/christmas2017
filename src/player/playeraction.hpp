#pragma once

#include <spr/hash/stringhash.hpp>

namespace PlayerAction
{
    constexpr spr::StringHash Up = "player_up"_hash;
    constexpr spr::StringHash Down = "player_down"_hash;
    constexpr spr::StringHash Left = "player_left"_hash;
    constexpr spr::StringHash Right = "player_right"_hash;
    constexpr spr::StringHash LoadPunch = "player_loadpunch"_hash;
}
