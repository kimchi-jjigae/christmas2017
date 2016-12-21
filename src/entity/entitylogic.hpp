#pragma once
#include <data.hpp>

class EntityLogic
{
    public:
        EntityLogic(GameData& data);
        void update();
    private:
        GameData& mData;
};
