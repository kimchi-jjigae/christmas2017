#include "chunklogic.hpp"
#include "chunk.hpp"
#include "tileutil.hpp"
#include <rendering/renderingutil.hpp>
#include <fea/rendering/tilemap.hpp>
#include <gamedata.hpp>

ChunkLogic::ChunkLogic(GameData& data):
    mData(data)
{
}

void ChunkLogic::update()
{
    //load pipeline
    loadPipeLine();

    //view detection
    for(const auto& coordinate : mData.chunksToPutInView)
    {
        TH_ASSERT(mData.chunksInView.count(coordinate) == 0, "Was about to emplace chunk in view, but it was already there " << coordinate);
        setupOverlay(coordinate, mData.chunksInView.emplace(coordinate, ChunkViewData{std::move(mData.chunkOverlayPool.back()), {}}).first->second, mData.worldChunks.at(coordinate), mData);
        mData.chunkOverlayPool.pop_back();
    }
    mData.chunksToPutInView.clear();

    for(const auto& coordinate : mData.chunksThatLeftView)
    {
        TH_ASSERT(mData.chunksInView.count(coordinate) != 0, "Was about to erase chunk from view, but it was not there " << coordinate);
        mData.chunkOverlayPool.emplace_back(std::move(mData.chunksInView.at(coordinate).overlayMasks));
        mData.chunksInView.erase(coordinate);
    }
    mData.chunksThatLeftView.clear();

    mData.chunksToBuildTileMap.clear();
}

void ChunkLogic::loadPipeLine()
{
    for(glm::ivec2 coordinate : mData.chunksToLoad)
    {
        TH_ASSERT(mData.worldChunks.count(coordinate) == 0, "cannot load already loaded chunk" << coordinate);
        Chunk& chunk = mData.worldChunks[coordinate];

        size_t tileIndex = 0;
        for(int32_t y = 0; y < ChunkWidth; ++y)
        {
            bool path = y % 8 == 0;
            for(int32_t x = 0; x < ChunkWidth; ++x)
            {
                glm::vec2 simplexCoord = glm::vec2((coordinate * ChunkWidth + glm::ivec2(x, y)) * TileWidth) / 9200.0f;
                int32_t goodness = static_cast<int32_t>((glm::simplex(simplexCoord) + 1.0f) / 2.0f) * 100;
                goodness = std::max(0, std::min(99, goodness));
                chunk.tiles[tileIndex] = path ? Tile{TileType::Path, goodness} : ((rand() % 8 != 0) ? Tile{TileType::Grass, goodness} : Tile{TileType::Trees, goodness});
                ++tileIndex;
            }
        }

        mData.chunksToBuildTileMap.emplace_back(coordinate);
    }

    mData.chunksToLoad.clear();

    for(glm::ivec2 coordinate : mData.chunksToBuildTileMap)
    {
        TH_ASSERT(mData.worldTileMaps.count(coordinate) == 0, "cannot setup tiles when already setup");
        LayeredTiles& tiles = mData.worldTileMaps.emplace(coordinate, LayeredTiles
        {
            createTileMap(TileLayer::Background, coordinate, mData),
            createTileMap(TileLayer::Center, coordinate, mData),
        }).first->second;

        const Chunk& chunk = mData.worldChunks.at(coordinate);

        size_t tileIndex = 0;
        for(int32_t y = 0; y < ChunkWidth; ++y)
        {
            for(int32_t x = 0; x < ChunkWidth; ++x)
            {
                setTile({x, y}, chunk.tiles[tileIndex], tiles);
                ++tileIndex;
            }
        }
    }

}
