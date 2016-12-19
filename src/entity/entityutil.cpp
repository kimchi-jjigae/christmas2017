#include "entityutil.hpp"
#include <data.hpp>

int32_t addEntity(Entity entity, GameData& data)
{
    int32_t newId = insert(std::move(entity.position), data.tPosition).id;

    for(auto sprite : entity.sprites)
    {
        Sprite newSprite
        {
            {}//type
            //pos
            //size
            //texture
        };

        if(type == Sprite::AnimatedSprite)
        {
            int32_t spriteId = insertAnimatedSprite(std::move(newSprite),
            AnimatedSprite
            {
                int32_t animation;
                int32_t animationClock;
            }, data);
        }
        else if(type == Sprite::FourDirectionalSprite)
        {
            int32_t spriteId = insertFourDirectionalSprite(std::move(newSprite),
            FourDirectionalSprite
            {
                Direction currentDirection;
                int32_t upAnimation;
                int32_t downAnimation;
                int32_t leftAnimation;
                int32_t rightAnimation;
                int32_t animationClock;
            }, data);
        }
    }

    return newId;
}
