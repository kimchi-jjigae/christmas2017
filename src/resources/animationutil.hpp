#pragma once
#include <data.hpp>
#include <thero/optional.hpp>

int32_t addSpriteAnimation(StringHash hash, SpriteAnimation animation, GameData& data);
th::Optional<int32_t> findAnimation(StringHash hash, GameData& data);
int32_t addFourDirectionalAnimationGroup(StringHash hash, FourDirectionalAnimationGroup animationGroup, GameData& data);
th::Optional<int32_t> findFourDirectionalAnimationGroup(StringHash hash, GameData& data);
