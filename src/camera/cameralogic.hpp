#pragma once

struct GameData;

class CameraLogic
{
    public:
        CameraLogic(GameData& data);
        void update();
    private:
        GameData& mData;
};
