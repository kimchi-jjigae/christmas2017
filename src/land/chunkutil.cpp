#include "chunkutil.hpp"

glm::vec2 chunkToWorld(glm::ivec2 chunkCoordinate)
{
    return chunkCoordinate * ChunkWidth * TileWidth;
}

glm::ivec2 worldToTile(glm::vec2 worldCoordinate)
{
    return static_cast<glm::ivec2>(worldCoordinate) / TileWidth;
}

glm::ivec2 tileToChunk(glm::ivec2 tileCoordinate)
{
    return tileCoordinate / ChunkWidth;
}

glm::ivec2 tileToChunkTile(glm::ivec2 tileCoordinate)
{
    return tileCoordinate % ChunkWidth;
}

size_t tileIndex(glm::ivec2 chunkTileCoordinate)
{
    return chunkTileCoordinate.x + chunkTileCoordinate.y * ChunkWidth;
}
