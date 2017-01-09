#pragma once
#include <fea/rendering/texture.hpp>
#include <thero/optional.hpp>
#include <string>
#include <spr/hash/stringhash.hpp>
#include <spr/data/tables.hpp>
#include <spr/data/texture.hpp>

int32_t loadAndAddTexture(spr::StringHash hash, const std::string& path, spr::Tables& tables);
int32_t addTexture(spr::StringHash hash, spr::Texture texture, spr::Tables& tables);
th::Optional<int32_t> findTexture(spr::StringHash hash, spr::Tables& tables);
const fea::Texture& getFeaTexture(int32_t textureId, spr::Tables& tables);
