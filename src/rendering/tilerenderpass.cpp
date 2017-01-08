#include "tilerenderpass.hpp"
#include <spr/rendering/rendercontext.hpp>

spr::RenderPass<GameData> createTileRenderPass()
{
    return
    {
        spr::RenderPass<GameData>::AllocateFunction(nullptr),
        spr::RenderPass<GameData>::PreRenderFunction(nullptr),
        spr::RenderPass<GameData>::RenderFunction([](spr::RenderContext& context, GameData& data)
        {
            context.renderer.setViewport(data.defaultViewport);

            for(const auto& tileIter : data.worldTileMaps)
            {
                context.renderer.render(tileIter.second.background);
                context.renderer.render(tileIter.second.center);
            }
        }),
        spr::RenderPass<GameData>::ResizeFunction(nullptr),
        spr::RenderPass<GameData>::PostRenderFunction(nullptr),
        spr::RenderPass<GameData>::DeallocateFunction(nullptr),
    };
}
