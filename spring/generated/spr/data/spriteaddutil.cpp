#include "spriteaddutil.hpp"
#include <spr/data/fourdirectionalsprite.hpp>
#include <spr/data/animatedsprite.hpp>

namespace spr
{
int32_t insertSprite(struct Sprite sprite, FourDirectionalSprite fourdirectionalsprite, Tables& tables)
{
    sprite.type = Sprite::FourDirectionalSprite;
    int32_t newId = insert(std::move(sprite), *tables.tSprite).id;
    insert(newId, std::move(fourdirectionalsprite), *tables.tFourDirectionalSprite);

    return newId;
}
int32_t insertSprite(struct Sprite sprite, AnimatedSprite animatedsprite, Tables& tables)
{
    sprite.type = Sprite::AnimatedSprite;
    int32_t newId = insert(std::move(sprite), *tables.tSprite).id;
    insert(newId, std::move(animatedsprite), *tables.tAnimatedSprite);

    return newId;
}

void eraseSprite(int32_t id, Tables& tables)
{
    erase(id, *tables.tSprite);
    erase(id, *tables.tFourDirectionalSprite);
    erase(id, *tables.tAnimatedSprite);
}
}
