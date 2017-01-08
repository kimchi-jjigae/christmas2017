#include "spriterenderpass.hpp"
#include <spr/rendering/rendercontext.hpp>
#include <spr/data/sprite.hpp>
#include <spr/data/spriteanimation.hpp>
#include <spr/data/animatedsprite.hpp>
#include <spr/data/fourdirectionalsprite.hpp>
#include <spr/data/fourdirectionalanimationgroup.hpp>
#include <spr/data/texture.hpp>

spr::RenderPass<GameData> createSpriteRenderPass()
{
    return
    {
        spr::RenderPass<GameData>::AllocateFunction(nullptr),
        spr::RenderPass<GameData>::PreRenderFunction(nullptr),
        spr::RenderPass<GameData>::RenderFunction([](spr::RenderContext& context, GameData& data)
        {
            context.renderer.setViewport(data.defaultViewport);

            forEach([&](int32_t id, const spr::Sprite& sprite)
            {
                if(sprite.type == spr::Sprite::_Base)
                {            
                    fea::Quad quad(sprite.size);
                    quad.setPosition(sprite.position);
                    quad.setTexture(*get(sprite.texture, data.spr.t<spr::TTexture>()).texture);
                    context.renderer.render(quad);
                }
                else if(sprite.type == spr::Sprite::AnimatedSprite)
                {
                    fea::AnimatedQuad quad(sprite.size);
                    quad.setPosition(sprite.position);
                    quad.setTexture(*get(sprite.texture, data.spr.t<spr::TTexture>()).texture);

                    const spr::AnimatedSprite& animSprite = get(id, data.spr.t<spr::TAnimatedSprite>());
                    const spr::SpriteAnimation& animation = get(animSprite.animation, data.spr.t<spr::TSpriteAnimation>());

                    fea::Animation feaAnimation
                    {
                        animation.start,
                        animation.size,
                        static_cast<uint32_t>(animation.frameAmount),
                        static_cast<uint32_t>(animation.frameTime),
                    };

                    quad.setAnimation(feaAnimation);

                    int32_t totalTickAmount = animation.frameAmount * animation.frameTime;
                    int32_t toTick = animSprite.animationClock % totalTickAmount;

                    for(int32_t i = 0; i < toTick; ++i)
                        quad.tick();

                    context.renderer.render(quad);
                }
                else if(sprite.type == spr::Sprite::FourDirectionalSprite)
                {
                    fea::AnimatedQuad quad(sprite.size);
                    quad.setPosition(sprite.position);
                    quad.setTexture(*get(sprite.texture, data.spr.t<spr::TTexture>()).texture);

                    const spr::FourDirectionalSprite& animSprite = get(id, data.spr.t<spr::TFourDirectionalSprite>());
                    const spr::FourDirectionalAnimationGroup& animGroup = get(animSprite.animationGroup, data.spr.t<spr::TFourDirectionalAnimationGroup>());

                    int32_t animationId = 0;

                    if(animSprite.currentOrientation == spr::Orientation::Up)
                        animationId = animGroup.up;
                    else if(animSprite.currentOrientation == spr::Orientation::Down)
                        animationId = animGroup.down;
                    else if(animSprite.currentOrientation == spr::Orientation::Left)
                        animationId = animGroup.left;
                    else if(animSprite.currentOrientation == spr::Orientation::Right)
                        animationId = animGroup.right;
                    const spr::SpriteAnimation& animation = get(animationId, data.spr.t<spr::TSpriteAnimation>());

                    fea::Animation feaAnimation
                    {
                        animation.start,
                        animation.size,
                        static_cast<uint32_t>(animation.frameAmount),
                        static_cast<uint32_t>(animation.frameTime),
                    };

                    quad.setAnimation(feaAnimation);

                    int32_t totalTickAmount = animation.frameAmount * animation.frameTime;
                    int32_t toTick = animSprite.animationClock % totalTickAmount;

                    for(int32_t i = 0; i < toTick; ++i)
                        quad.tick();

                    context.renderer.render(quad);
                }
            }, data.spr.t<spr::TSprite>());
        }),
        spr::RenderPass<GameData>::ResizeFunction(nullptr),
        spr::RenderPass<GameData>::PostRenderFunction(nullptr),
        spr::RenderPass<GameData>::DeallocateFunction(nullptr),
    };
}
