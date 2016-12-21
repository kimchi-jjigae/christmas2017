#pragma once
#include <cstdint>

enum TileType { Grass, Trees, Path };

constexpr int32_t TileWidth = 64;

struct Tile
{
    TileType type;
    int32_t goodness;
};
