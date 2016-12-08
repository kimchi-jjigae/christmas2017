#pragma once
#include <data.hpp>

void initializeChunkMasks(GameData& data);
void setupOverlay(glm::ivec2 chunkCoordinate, ChunkViewData& overlayData, const Chunk& chunk, GameData& data);
