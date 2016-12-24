#include "cameralogic.hpp"

CameraLogic::CameraLogic(GameData& data):
    mData(data)
{
}

void CameraLogic::update()
{
    if(mData.camera.cameraEntity)
    {
        mData.camera.position = get(*mData.camera.cameraEntity, mData.tPosition).coordinate;
    }

    glm::ivec2 size = mData.defaultViewport.getSize();

    auto start = mData.camera.position - size / 2;
    auto end = mData.camera.position + size / 2;

    std::unordered_set<glm::ivec2> points =
    {
        {start.x, start.y},
        {start.x, end.y},
        {end.x, start.y},
        {end.x, end.y},
    };
    
    std::unordered_set<glm::ivec2> chunksThatWereInView;

    for(auto point : points)
    {
        auto chunkCoord = point / TileWidth / ChunkWidth;

        if(mData.worldChunks.count(chunkCoord) == 0 && std::count(mData.chunksToLoad.begin(), mData.chunksToLoad.end(), chunkCoord) == 0)
        {
            mData.chunksToLoad.emplace_back(chunkCoord);
        }

        if(mData.chunksInView.count(chunkCoord) == 0 && std::count(mData.chunksToPutInView.begin(), mData.chunksToPutInView.end(), chunkCoord) == 0)
            mData.chunksToPutInView.emplace_back(chunkCoord);
        chunksThatWereInView.emplace(chunkCoord);
    }

    for(const auto& iter : mData.chunksInView)
    {
        if(chunksThatWereInView.count(iter.first) == 0)
            mData.chunksThatLeftView.emplace_back(iter.first);
    }
}
