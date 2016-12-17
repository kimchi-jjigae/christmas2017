//land
std::deque<glm::ivec2> chunksToLoad;
std::deque<glm::ivec2> chunksToBuildTileMap;
std::unordered_map<glm::ivec2, Chunk> worldChunks;

//system
glm::ivec2 screenSize = initialScreenSize;

//rendering
std::map<int32_t, RenderPass> renderPasses;
fea::Camera worldCamera;
fea::Viewport defaultViewport;
fea::Camera guiCamera;
fea::Viewport guiViewport;
fea::Camera overlayCamera;
fea::Viewport overlayViewport;
EffectOverlayData effectOverlayData;

//graphics
glm::ivec2 cameraPosition;
float zoom = 1.0f;
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
Direction currentDirection = None;
