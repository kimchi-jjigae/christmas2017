#pragma once

struct GameData;

class EntityLogic
{
    public:
        EntityLogic(GameData& data);
        void update();
    private:
        GameData& mData;
};
