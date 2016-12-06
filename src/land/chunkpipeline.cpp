#include "chunkpipeline.hpp"
#include "chunk.hpp"
#include <fea/rendering/tilemap.hpp>

ChunkPipeline::ChunkPipeline(GameData& data):
    mData(data)
{
}

void ChunkPipeline::update()
{
    for(glm::ivec2 coordinate : mData.chunksToLoad)
    {
        TH_ASSERT(mData.worldChunks.count(coordinate) == 0, "cannot load already loaded chunk");
        Chunk& chunk = mData.worldChunks[coordinate];

        size_t tileIndex = 0;
        for(int32_t y = 0; y < ChunkWidth; ++y)
        {
            for(int32_t x = 0; x < ChunkWidth; ++x)
            {
                chunk.tiles[tileIndex] = (rand() % 8 != 0) ? Tile{TileType::GRASS} : Tile{TileType::TREES};
                ++tileIndex;
            }
        }

        mData.chunksToBuildTileMap.emplace_back(coordinate);
    }

    mData.chunksToLoad.clear();

    for(glm::ivec2 coordinate : mData.chunksToBuildTileMap)
    {
        TH_ASSERT(mData.worldTileMaps.count(coordinate) == 0, "cannot setup tiles when already setup");
        fea::TileMap& tiles = mData.worldTileMaps.emplace(coordinate, fea::TileMap({64, 64} , {TileWidth, TileWidth})).first->second;

        tiles.addTileDefinition(TileType::GRASS, fea::TileDefinition{{0,0}});
        tiles.addTileDefinition(TileType::TREES, fea::TileDefinition{{1,0}});
        tiles.setTexture(mData.tilesTexture);

        const Chunk& chunk = mData.worldChunks.at(coordinate);

        size_t tileIndex = 0;
        for(int32_t y = 0; y < ChunkWidth; ++y)
        {
            for(int32_t x = 0; x < ChunkWidth; ++x)
            {
                tiles.setTile({x, y}, chunk.tiles[tileIndex].type);
                ++tileIndex;
            }
        }
    }

    mData.chunksToBuildTileMap.clear();
}
