#pragma once
#include <data.hpp>
#include <thero/optional.hpp>

int32_t addSpriteAnimation(StringHash hash, SpriteAnimation animation, GameData& data);
th::Optional<int32_t> findAnimation(StringHash hash, GameData& data);
