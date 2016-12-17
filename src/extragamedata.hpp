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
//graphics
glm::ivec2 cameraPosition;
float zoom = 1.0f;
std::unordered_map<glm::ivec2, LayeredTiles> worldTileMaps;
fea::Texture tilesBackgroundTexture;
fea::Texture tilesCenterTexture;
fea::Texture fogTexture;
fea::Texture noiseTexture;
fea::Texture wizardTexture;
std::deque<std::array<fea::Texture, 4>> chunkOverlayPool;
std::deque<glm::ivec2> chunksToPutInView;
std::unordered_map<glm::ivec2, ChunkViewData> chunksInView;
std::deque<glm::ivec2> chunksThatLeftView;
Direction currentDirection = None;
