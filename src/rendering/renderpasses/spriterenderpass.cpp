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
                fea::Quad quad(sprite.size);
                quad.setPosition(sprite.position);
                quad.setTexture(*get(sprite.texture, data.tTexture).texture);
                context.renderer.render(quad);
            }, data.tSprite);
        }),
        ResizeFunction(nullptr),
        PostRenderFunction(nullptr),
        DeallocateFunction(nullptr),
    };
}
