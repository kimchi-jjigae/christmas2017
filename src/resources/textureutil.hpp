#pragma once
#include <fea/rendering/texture.hpp>
#include <thero/optional.hpp>
#include <string>
#include "../stringhash.hpp"
#include <data.hpp>

int32_t loadAndAddTexture(StringHash hash, const std::string& path, GameData& data);
int32_t addTexture(StringHash hash, Texture texture, GameData& data);
th::Optional<int32_t> findTexture(StringHash hash, GameData& data);
const fea::Texture& getFeaTexture(int32_t textureId, GameData& data);
