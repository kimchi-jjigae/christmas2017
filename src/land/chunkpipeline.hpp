#pragma once
#include <data.hpp>

class ChunkPipeline
{
    public:
        ChunkPipeline(GameData& data);
        void update();
    private:
        GameData& mData;
};
