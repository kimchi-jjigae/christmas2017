#pragma once

#include <functional>

enum class PlayerAction { Throttle, Reverse, TurnLeft, TurnRight, StrafeLeft, StrafeRight, Fire };

namespace std
{
    template<> struct hash<PlayerAction>
    {
        size_t operator()(PlayerAction playerAction) const
        {
	        return static_cast<size_t>(playerAction);
        }
    };
}
