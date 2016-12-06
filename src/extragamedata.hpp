
std::deque<glm::ivec2> chunksToLoad;
std::deque<glm::ivec2> chunksToBuildTileMap;
std::unordered_map<glm::ivec2, Chunk> worldChunks;

std::unordered_map<glm::ivec2, fea::TileMap> worldTileMaps;
fea::Texture tilesTexture;
