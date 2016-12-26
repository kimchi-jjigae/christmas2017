#include "textureutil.hpp"
#include "texturemaker.hpp"
#include <data.hpp>

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

th::Optional<int32_t> findTexture(StringHash hash, GameData& data)
{
    auto found = findOne([&](int32_t id, const TextureIndex& textureIndex)
    {
        return textureIndex.hash == hash;
    }, data.tTextureIndex);

    if(found)
        return {found->id};
    else
        return {};
}

const fea::Texture& getFeaTexture(int32_t textureId, GameData& data)
{
    return *get(textureId, data.tTexture).texture;
}
