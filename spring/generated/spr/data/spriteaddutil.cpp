#include "spriteaddutil.hpp"
#include <spr/data/fourdirectionalsprite.hpp>
#include <spr/data/animatedsprite.hpp>

namespace spr
{
int32_t insertSprite(struct Sprite sprite, FourDirectionalSprite fourdirectionalsprite, TableModule& tables)
{
    sprite.type = Sprite::FourDirectionalSprite;
    int32_t newId = insert(std::move(sprite), tables.t<TSprite>()).id;
    insert(newId, std::move(fourdirectionalsprite), tables.t<TFourDirectionalSprite>());

    return newId;
}
int32_t insertSprite(struct Sprite sprite, AnimatedSprite animatedsprite, TableModule& tables)
{
    sprite.type = Sprite::AnimatedSprite;
    int32_t newId = insert(std::move(sprite), tables.t<TSprite>()).id;
    insert(newId, std::move(animatedsprite), tables.t<TAnimatedSprite>());

    return newId;
}

void eraseSprite(int32_t id, TableModule& tables)
{
    erase(id, tables.t<TSprite>());
    erase(id, tables.t<TFourDirectionalSprite>());
    erase(id, tables.t<TAnimatedSprite>());
}
}
