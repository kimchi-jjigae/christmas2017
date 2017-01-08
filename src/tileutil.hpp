#pragma once
#include <fea/rendering/tilemap.hpp>
#include <spr/glm.hpp>
#include <layeredtiles.hpp>
#include <land/tile.hpp>

struct GameData;

enum GfxBackgroundTile { Grass0, Grass1, Grass2, Grass3, 
                         Path0, Path1, Path2, Path3 };
enum GfxCenterTile { Trees0, Trees1, Trees2, Trees3 };

enum TileLayer { Background, Center };

fea::TileMap createTileMap(TileLayer layer, glm::ivec2 chunkCoordinate, GameData& data);
void setTile(glm::ivec2 coordinate, Tile tile, LayeredTiles& tiles);

void setTileGoodness(glm::ivec2 tileCoord, int32_t goodness, GameData& data);
int32_t tileGoodness(glm::ivec2 tileCoord, GameData& data);
