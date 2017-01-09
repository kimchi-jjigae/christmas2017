#include "textureutil.hpp"
#include "texturemaker.hpp"
#include <spr/data/textureindex.hpp>

int32_t loadAndAddTexture(spr::StringHash hash, const std::string& path, spr::Tables& tables)
{
    return addTexture(hash, spr::Texture{std::make_shared<fea::Texture>(makeTexture(path))}, tables);
}

int32_t addTexture(spr::StringHash hash, spr::Texture texture, spr::Tables& tables)
{
    int32_t newId = insert(std::move(texture), *tables.tTexture).id;
    insert(spr::TextureIndex{hash, newId}, *tables.tTextureIndex);
    return newId;
}

th::Optional<int32_t> findTexture(spr::StringHash hash, spr::Tables& tables)
{
    auto found = findOne([&](int32_t id, const spr::TextureIndex& textureIndex)
    {
        return textureIndex.hash == hash;
    }, *tables.tTextureIndex);

    if(found)
        return {found->id};
    else
        return {};
}

const fea::Texture& getFeaTexture(int32_t textureId, spr::Tables& tables)
{
    return *get(textureId, *tables.tTexture).texture;
}
