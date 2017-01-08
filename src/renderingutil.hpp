#pragma once
#include <spr/glm.hpp>

struct GameData;
struct ChunkViewData;
struct Chunk;

void initializeChunkMasks(GameData& data);
void setupOverlay(glm::ivec2 chunkCoordinate, ChunkViewData& overlayData, const Chunk& chunk, GameData& data);
