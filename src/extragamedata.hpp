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
std::map<int32_t, RenderPass> renderPasses;
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
