#include "textureutil.hpp"
#include "texturemaker.hpp"
#include <spr/data/textureindex.hpp>

int32_t loadAndAddTexture(spr::StringHash hash, const std::string& path, spr::TableModule& tables)
{
    return addTexture(hash, spr::Texture{std::make_shared<fea::Texture>(makeTexture(path))}, tables);
}

int32_t addTexture(spr::StringHash hash, spr::Texture texture, spr::TableModule& tables)
{
    int32_t newId = insert(std::move(texture), tables.t<spr::TTexture>()).id;
    insert(spr::TextureIndex{hash, newId}, tables.t<spr::TTextureIndex>());
    return newId;
}

th::Optional<int32_t> findTexture(spr::StringHash hash, spr::TableModule& tables)
{
    auto found = findOne([&](int32_t id, const spr::TextureIndex& textureIndex)
    {
        return textureIndex.hash == hash;
    }, tables.t<spr::TTextureIndex>());

    if(found)
        return {found->id};
    else
        return {};
}

const fea::Texture& getFeaTexture(int32_t textureId, spr::TableModule& tables)
{
    return *get(textureId, tables.t<spr::TTexture>()).texture;
}
