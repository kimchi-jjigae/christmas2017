#include "tileutil.hpp"

fea::TileMap createTileMap(TileLayer layer, glm::ivec2 chunkCoordinate, GameData& data)
{
    fea::TileMap result({TileWidth, TileWidth} , {16, 16});

    if(layer == TileLayer::Background)
    {
        result.addTileDefinition(GfxBackgroundTile::Grass0, fea::TileDefinition{{0,0}});
        result.addTileDefinition(GfxBackgroundTile::Grass1, fea::TileDefinition{{1,0}});
        result.addTileDefinition(GfxBackgroundTile::Grass2, fea::TileDefinition{{2,0}});
        result.addTileDefinition(GfxBackgroundTile::Grass3, fea::TileDefinition{{3,0}});
        result.addTileDefinition(GfxBackgroundTile::Path0, fea::TileDefinition{{4,0}});
        result.addTileDefinition(GfxBackgroundTile::Path1, fea::TileDefinition{{5,0}});
        result.addTileDefinition(GfxBackgroundTile::Path2, fea::TileDefinition{{6,0}});
        result.addTileDefinition(GfxBackgroundTile::Path3, fea::TileDefinition{{7,0}});
        result.setTexture(data.tilesBackgroundTexture);
    }
    else if(layer == TileLayer::Center)
    {
        result.addTileDefinition(GfxCenterTile::Trees0, fea::TileDefinition{{0,0}});
        result.addTileDefinition(GfxCenterTile::Trees1, fea::TileDefinition{{1,0}});
        result.addTileDefinition(GfxCenterTile::Trees2, fea::TileDefinition{{2,0}});
        result.addTileDefinition(GfxCenterTile::Trees3, fea::TileDefinition{{3,0}});
        result.setTexture(data.tilesCenterTexture);
    }
    else
    {
        TH_ASSERT(false, "unknown tile layer");
    }

    result.setPosition(chunkCoordinate * ChunkWidth * TileWidth);

    return result;
}

void setTile(glm::ivec2 coordinate, Tile tile, LayeredTiles& tiles)
{
    int32_t goodness = tile.goodness;
    TH_ASSERT(goodness < 100 && goodness >= 0, "Goodness value invalid: " << goodness);
    int32_t goodnessOffset = goodness / 25;

    if(tile.type == TileType::Trees)
    {
        tiles.background.setTile(coordinate, GfxBackgroundTile::Grass0 + goodnessOffset);
        tiles.center.setTile(coordinate, GfxCenterTile::Trees0 + goodnessOffset);
    }
    else if(tile.type == TileType::Path)
    {
        tiles.background.setTile(coordinate, GfxBackgroundTile::Path0 + goodnessOffset);
        tiles.center.unsetTile(coordinate);
    }
    else if(tile.type == TileType::Grass)
    {
        tiles.background.setTile(coordinate, GfxBackgroundTile::Grass0 + goodnessOffset);
        tiles.center.unsetTile(coordinate);
    }
}
