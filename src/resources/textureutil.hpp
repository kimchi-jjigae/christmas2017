#pragma once
#include <fea/rendering/texture.hpp>
#include <thero/optional.hpp>
#include <string>
#include <spr/hash/stringhash.hpp>
#include <spr/tables/tablemodule.hpp>
#include <spr/data/texture.hpp>

int32_t loadAndAddTexture(spr::StringHash hash, const std::string& path, spr::TableModule& tables);
int32_t addTexture(spr::StringHash hash, spr::Texture texture, spr::TableModule& tables);
th::Optional<int32_t> findTexture(spr::StringHash hash, spr::TableModule& tables);
const fea::Texture& getFeaTexture(int32_t textureId, spr::TableModule& tables);
