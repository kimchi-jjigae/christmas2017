#pragma once
#include <data.hpp>

class EntityStatesLogic
{
    public:
        EntityStatesLogic(GameData& data);
        void update();
    private:
        GameData& mData;
};
