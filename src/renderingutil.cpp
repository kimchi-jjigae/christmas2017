#include "renderingutil.hpp"
#include "land/chunkutil.hpp"
#include "land/goodness.hpp"

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
                int32_t goodLevelAmount = goodnessLevelAmount(static_cast<GoodnessLevel>(goodnessLevel), goodness);
                int32_t color = goodLevelAmount / 100.0f * 255;

                overlayData.overlayMasks[goodnessLevel].setPixel({x, y}, fea::Color(color, color, color, color));
                ++tileIndex;
            }
        }

        overlayData.overlayMasks[goodnessLevel].update();
    }

    overlayData.overlayQuad.setSize(glm::ivec2{chunkSize, chunkSize});
    overlayData.overlayQuad.setPosition(position);
    overlayData.overlayQuad.setTexture(overlayData.overlayMasks[1]);

    overlayData.overlayDecorationQuad.setSize(glm::ivec2{chunkSize, chunkSize});
    overlayData.overlayDecorationQuad.setPosition(position);
    if(
    overlayData.overlayDecorationQuad.setOpacity(0.8f);
    overlayData.overlayDecorationQuad.setTexture(data.fogTexture);
    overlayData.overlayDecorationQuad.setTileSize(glm::ivec2{256, 256});
    overlayData.overlayDecorationQuad.setScrollSpeed({-1.0001f, 0.0f});
}
