#include "tilerenderpass.hpp"
#include <spr/rendering/rendercontext.hpp>
#include <spr/data/view.hpp>
#include <gamedata.hpp>

spr::RenderPass createTileRenderPass(GameData& data)
{
    return
    {
        spr::AllocateFunction(nullptr),
        spr::PreRenderFunction(nullptr),
        spr::RenderFunction([&](spr::RenderContext& context)
        {
            fea::Viewport& worldViewport = get(data.worldView, *data.spr.tView).viewport;
            context.renderer.setViewport(worldViewport);

            for(const auto& tileIter : data.worldTileMaps)
            {
                context.renderer.render(tileIter.second.background);
                context.renderer.render(tileIter.second.center);
            }
        }),
        spr::ResizeFunction(nullptr),
        spr::PostRenderFunction(nullptr),
        spr::DeallocateFunction(nullptr),
    };
}
