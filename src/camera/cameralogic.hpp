#pragma once
#include <data.hpp>

class CameraLogic
{
    public:
        CameraLogic(GameData& data);
        void update();
    private:
        GameData& mData;
};
