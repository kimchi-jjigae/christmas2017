#pragma once
#include "chunk.hpp"
#include <glm.hpp>

glm::vec2 chunkToWorld(glm::ivec2 chunkCoordinate);
glm::ivec2 worldToTile(glm::vec2 worldCoordinate);
glm::ivec2 tileToChunk(glm::ivec2 tileCoordinate);
glm::ivec2 tileToChunkTile(glm::ivec2 tileCoordinate);
size_t tileIndex(glm::ivec2 chunkTileCoordinate);
