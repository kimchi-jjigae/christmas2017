#pragma once
#include <thero/optional.hpp>
#include <spr/tables/tablemodule.hpp>
#include <spr/hash/stringhash.hpp>
#include <spr/data/spriteanimation.hpp>
#include <spr/data/fourdirectionalsprite.hpp>
#include <spr/data/fourdirectionalanimationgroup.hpp>

int32_t addSpriteAnimation(spr::StringHash hash, spr::SpriteAnimation animation, spr::TableModule& tables);
th::Optional<int32_t> findAnimation(spr::StringHash hash, spr::TableModule& tables);
int32_t addFourDirectionalAnimationGroup(spr::StringHash hash, spr::FourDirectionalAnimationGroup animationGroup, spr::TableModule& tables);
th::Optional<int32_t> findFourDirectionalAnimationGroup(spr::StringHash hash, spr::TableModule& tables);
