#pragma once

enum TileType { Grass, Trees, Path };

struct Tile
{
    TileType type;
    int32_t goodness;
};
