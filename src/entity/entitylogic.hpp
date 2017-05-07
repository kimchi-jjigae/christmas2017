#pragma once

struct GameData;

class EntityLogic
{
    public:
        EntityLogic(GameData& data);
        void update();
        void updateSpatialTree();
    private:
        GameData& mData;
};
