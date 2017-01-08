#include "spriterenderpass.hpp"
#include <spr/rendering/rendercontext.hpp>
#include <spr/debug/debugrenderer.hpp>

spr::RenderPass<GameData> createDebugRenderPass()
{
    return
    {
        spr::RenderPass<GameData>::AllocateFunction([](fea::Renderer2D& renderer, GameData& data)
        {
            spr::DRen::initialize(renderer, data.worldCamera);
        }),
        spr::RenderPass<GameData>::PreRenderFunction(nullptr),
        spr::RenderPass<GameData>::RenderFunction([](spr::RenderContext& context, GameData& data)
        {
            spr::DRen::setCamera(data.worldCamera);
            spr::DRen::flush();
        }),
        spr::RenderPass<GameData>::ResizeFunction(nullptr),
        spr::RenderPass<GameData>::PostRenderFunction(nullptr),
        spr::RenderPass<GameData>::DeallocateFunction(nullptr),
    };
}
