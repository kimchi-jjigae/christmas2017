#include "spriterenderpass.hpp"
#include <spr/rendering/rendercontext.hpp>
#include <spr/data/sprite.hpp>
#include <spr/data/view.hpp>
#include <spr/data/spriteanimation.hpp>
#include <spr/data/animatedsprite.hpp>
#include <spr/data/fourdirectionalsprite.hpp>
#include <spr/data/fourdirectionalanimationgroup.hpp>
#include <spr/data/texture.hpp>

namespace spr
{
spr::RenderPass createSpriteRenderPass(dpx::TableId viewId, spr::Tables& tables)
{
    return
    {
        spr::AllocateFunction(nullptr),
        spr::PreRenderFunction(nullptr),
        spr::RenderFunction([viewId, &tables](spr::RenderContext& context)
        {
            fea::Viewport& viewport = get(viewId, *tables.tView).viewport;

            context.renderer.setViewport(viewport);

            forEach([&](int32_t id, const spr::Sprite& sprite)
            {
                if(sprite.type == spr::Sprite::_Base)
                {            
                    fea::Quad quad(sprite.size);
                    quad.setPosition(sprite.position);
                    quad.setTexture(*get(sprite.texture, *tables.tTexture).texture);
                    context.renderer.render(quad);
                }
                else if(sprite.type == spr::Sprite::AnimatedSprite)
                {
                    fea::AnimatedQuad quad(sprite.size);
                    quad.setPosition(sprite.position);
                    quad.setTexture(*get(sprite.texture, *tables.tTexture).texture);

                    const spr::AnimatedSprite& animSprite = get(id, *tables.tAnimatedSprite);
                    const spr::SpriteAnimation& animation = get(animSprite.animation, *tables.tSpriteAnimation);

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
                    quad.setTexture(*get(sprite.texture, *tables.tTexture).texture);

                    const spr::FourDirectionalSprite& animSprite = get(id, *tables.tFourDirectionalSprite);
                    const spr::FourDirectionalAnimationGroup& animGroup = get(animSprite.animationGroup, *tables.tFourDirectionalAnimationGroup);

                    int32_t animationId = 0;

                    if(animSprite.currentOrientation == spr::Orientation::Up)
                        animationId = animGroup.up;
                    else if(animSprite.currentOrientation == spr::Orientation::Down)
                        animationId = animGroup.down;
                    else if(animSprite.currentOrientation == spr::Orientation::Left)
                        animationId = animGroup.left;
                    else if(animSprite.currentOrientation == spr::Orientation::Right)
                        animationId = animGroup.right;
                    const spr::SpriteAnimation& animation = get(animationId, *tables.tSpriteAnimation);

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
            }, *tables.tSprite);
        }),
        spr::ResizeFunction(nullptr),
        spr::PostRenderFunction(nullptr),
        spr::DeallocateFunction(nullptr),
    };
}
}
