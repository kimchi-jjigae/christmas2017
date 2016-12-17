#pragma once
#include <data.hpp>

class ChunkLogic
{
    public:
        ChunkLogic(GameData& data);
        void update();
    private:
        void loadPipeLine();
        GameData& mData;
};
