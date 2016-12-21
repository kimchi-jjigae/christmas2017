#include "spriterenderpass.hpp"
#include "../rendercontext.hpp"
#include <data.hpp>

RenderPass createSpriteRenderPass()
{
    return
    {
        AllocateFunction(nullptr),
        PreRenderFunction(nullptr),
        RenderFunction([](RenderContext& context, GameData& data)
        {
            context.renderer.setViewport(data.defaultViewport);

            forEach([&](int32_t id, const Sprite& sprite)
            {
                if(sprite.type == Sprite::_Base)
                {            
                    fea::Quad quad(sprite.size);
                    quad.setPosition(sprite.position);
                    quad.setTexture(*get(sprite.texture, data.tTexture).texture);
                    context.renderer.render(quad);
                }
                else if(sprite.type == Sprite::AnimatedSprite)
                {
                    fea::AnimatedQuad quad(sprite.size);
                    quad.setPosition(sprite.position);
                    quad.setTexture(*get(sprite.texture, data.tTexture).texture);

                    const AnimatedSprite& animSprite = get(id, data.tAnimatedSprite);
                    const SpriteAnimation& animation = get(animSprite.animation, data.tSpriteAnimation);

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
                else if(sprite.type == Sprite::FourDirectionalSprite)
                {
                    TH_ASSERT(false, "tbi");
                    //tbi
                }
            }, data.tSprite);
        }),
        ResizeFunction(nullptr),
        PostRenderFunction(nullptr),
        DeallocateFunction(nullptr),
    };
}
