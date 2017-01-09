#pragma once

#include <cstdint>
#include <deque>
#include <unordered_map>
#include <map>
#include <unordered_set>
#include <dpx/tables.hpp>
#include <spr/glm.hpp>
#include <spr/rendering/renderpass.hpp>
#include <fea/rendering/camera.hpp>
#include <fea/rendering/viewport.hpp>
#include <camera/camera.hpp>
#include <rendering/effectoverlaydata.hpp>
#include <layeredtiles.hpp>
#include <chunkviewdata.hpp>
#include <startupconstants.hpp>
#include <land/chunk.hpp>
#include <player/playeraction.hpp>
#include <spr/data/tables.hpp>
#include <data/datatables.hpp>

struct GameData
{
    spr::Tables spr;
    GameTables game;

    //land
    std::deque<glm::ivec2> chunksToLoad;
    std::deque<glm::ivec2> chunksToBuildTileMap;
    std::unordered_map<glm::ivec2, Chunk> worldChunks;
    
    //system
    glm::ivec2 screenSize = initialScreenSize;
    
    //input
    std::unordered_set<PlayerAction> startedPlayerActions;
    std::unordered_set<PlayerAction> ongoingPlayerActions;
    std::unordered_set<PlayerAction> stoppedPlayerActions;
    
    //rendering
    std::map<int32_t, spr::RenderPass<GameData>> renderPasses;
    fea::Camera worldCamera;
    fea::Viewport defaultViewport;
    fea::Camera guiCamera;
    fea::Viewport guiViewport;
    fea::Camera overlayCamera;
    fea::Viewport overlayViewport;
    EffectOverlayData effectOverlayData;
    
    //entities
    dpx::IdSet entitiesToRemove;
    int32_t playerId;
    
    //graphics
    Camera camera;
    std::unordered_map<glm::ivec2, LayeredTiles> worldTileMaps;
    int32_t tilesBackgroundTexture;
    int32_t tilesCenterTexture;
    int32_t fogTexture;
    int32_t noiseTexture;
    int32_t wizardTexture;
    std::deque<std::array<fea::Texture, 4>> chunkOverlayPool;
    std::deque<glm::ivec2> chunksToPutInView;
    std::unordered_map<glm::ivec2, ChunkViewData> chunksInView;
    std::deque<glm::ivec2> chunksThatLeftView;
};
