#pragma once
#include <data.hpp>

class CollisionLogic
{
    public:
        CollisionLogic(GameData& data);
        void update();
    private:
        GameData& mData;
};
