#include "renderingutil.hpp"
#include "land/chunkutil.hpp"
#include "land/goodness.hpp"
#include <spr/data/view.hpp>
#include <gamedata.hpp>

void initializeChunkMasks(GameData& data)
{
    data.chunkOverlayPool.resize(4);
    for(int32_t i = 0; i < 4; ++i)
    {
        std::array<fea::Texture, 4>& overlays = data.chunkOverlayPool[i];
        for(fea::Texture& texture : overlays)
        {
            texture.create({ChunkWidth * 2, ChunkWidth * 2}, fea::Color::Transparent);
        }
    }
}

void setupOverlay(glm::ivec2 chunkCoordinate, ChunkViewData& overlayData, const Chunk& chunk, GameData& data)
{
    float chunkSize = ChunkWidth * TileWidth * 2;
    glm::vec2 position = chunkToWorld(chunkCoordinate);

    for(size_t goodnessLevel = 0; goodnessLevel < overlayData.overlayMasks.size(); ++goodnessLevel)
    {
        size_t tileIndex = 0;
        for(int32_t y = 0; y < ChunkWidth; ++y)
        {
            for(int32_t x = 0; x < ChunkWidth; ++x)
            {
                int32_t goodness = chunk.tiles[tileIndex].goodness;
                int32_t color = goodness / 100.0f * 255 + 35;

                overlayData.overlayMasks[goodnessLevel].setPixel({x, y}, fea::Color(color, color, color, color));
                ++tileIndex;
            }
        }

        overlayData.overlayMasks[goodnessLevel].update();
    }

    overlayData.overlayQuad.setSize(glm::ivec2{chunkSize, chunkSize});
    overlayData.overlayQuad.setPosition(position);
    overlayData.overlayQuad.setTexture(overlayData.overlayMasks[1]);
}

void resizeViewports(glm::ivec2 newSize, GameData& data)
{
    fea::Viewport& worldViewport = get(data.worldView, *data.spr.tView).viewport;

    auto cam = worldViewport.getCamera();
    worldViewport = fea::Viewport(newSize, {}, {});
    worldViewport.setCamera(cam);

    fea::Viewport& guiViewport = get(data.guiView, *data.spr.tView).viewport;

    cam = guiViewport.getCamera();
    guiViewport = fea::Viewport(newSize, {}, {});
    guiViewport.setCamera(cam);
}
