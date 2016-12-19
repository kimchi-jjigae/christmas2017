#include "entityutil.hpp"
#include <data.hpp>

int32_t addEntity(Entity entity, GameData& data)
{
    glm::vec2 position = entity.position.coordinate;
    int32_t newId = insert(std::move(entity.position), data.tPosition).id;

    for(auto sprite : entity.sprites)
    {
        Sprite newSprite
        {
            {},
            position + sprite.offset,
            sprite.size,
            sprite.texture,
        };

        if(sprite.type == Sprite::AnimatedSprite)
        {
            int32_t spriteId = insertAnimatedSprite(std::move(newSprite),
            AnimatedSprite
            {
                sprite.animatedSprite.animation,
                0,
            }, data);
        }
        else if(sprite.type == Sprite::FourDirectionalSprite)
        {
            int32_t spriteId = insertFourDirectionalSprite(std::move(newSprite),
            FourDirectionalSprite
            {
                Direction::Up,
                sprite.fourDirectionalSprite.upAnimation,
                sprite.fourDirectionalSprite.downAnimation,
                sprite.fourDirectionalSprite.leftAnimation,
                sprite.fourDirectionalSprite.rightAnimation,
                0,
            }, data);
        }
    }

    return newId;
}
