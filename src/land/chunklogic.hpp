#pragma once

struct GameData;

class ChunkLogic
{
    public:
        ChunkLogic(GameData& data);
        void update();
    private:
        void loadPipeLine();
        GameData& mData;
};
