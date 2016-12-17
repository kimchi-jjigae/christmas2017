#include "textureutil.hpp"
#include "texturemaker.hpp"

int32_t loadAndAddTexture(StringHash hash, const std::string& path, GameData& data)
{
    return addTexture(hash, Texture{std::make_shared<fea::Texture>(makeTexture(path))}, data);
}

int32_t addTexture(StringHash hash, Texture texture, GameData& data)
{
    int32_t newId = insert(std::move(texture), data.tTexture).id;
    insert(TextureIndex{hash, newId}, data.tTextureIndex);
    return newId;
}

const fea::Texture& getFeaTexture(int32_t textureId, GameData& data)
{
    return *get(textureId, data.tTexture).texture;
}
