#pragma once

struct GameData;

class PlayerLogic
{
    public:
        PlayerLogic(GameData& data);
        void update();
    private:
        GameData& mData;
};
