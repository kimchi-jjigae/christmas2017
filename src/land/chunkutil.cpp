#include "chunkutil.hpp"

glm::vec2 chunkToWorld(glm::ivec2 chunkCoordinate)
{
    return chunkCoordinate * ChunkWidth * TileWidth;
}
