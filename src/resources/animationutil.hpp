#pragma once
#include <thero/optional.hpp>
#include <spr/data/tables.hpp>
#include <spr/hash/stringhash.hpp>
#include <spr/data/spriteanimation.hpp>
#include <spr/data/fourdirectionalsprite.hpp>
#include <spr/data/fourdirectionalanimationgroup.hpp>

int32_t addSpriteAnimation(spr::StringHash hash, spr::SpriteAnimation animation, spr::Tables& tables);
th::Optional<int32_t> findAnimation(spr::StringHash hash, spr::Tables& tables);
int32_t addFourDirectionalAnimationGroup(spr::StringHash hash, spr::FourDirectionalAnimationGroup animationGroup, spr::Tables& tables);
th::Optional<int32_t> findFourDirectionalAnimationGroup(spr::StringHash hash, spr::Tables& tables);
