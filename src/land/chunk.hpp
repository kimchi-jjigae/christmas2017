#pragma once
#include "tile.hpp"
#include <array>

constexpr int32_t ChunkWidth = 64;
constexpr int32_t ChunkWidthP2 = ChunkWidth * ChunkWidth;

struct Chunk
{
    std::array<Tile, ChunkWidthP2> tiles;
};
