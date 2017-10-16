#pragma once

#include <functional>

enum class PlayerAction { Up, Down, Left, Right, LoadPunch };

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
