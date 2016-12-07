
//land
std::deque<glm::ivec2> chunksToLoad;
std::deque<glm::ivec2> chunksToBuildTileMap;
std::unordered_map<glm::ivec2, Chunk> worldChunks;

//graphics
glm::ivec2 cameraPosition;
std::unordered_map<glm::ivec2, LayeredTiles> worldTileMaps;
fea::Texture tilesBackgroundTexture;
fea::Texture tilesCenterTexture;
