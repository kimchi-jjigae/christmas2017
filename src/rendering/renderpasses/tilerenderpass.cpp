#include "imguirenderpass.hpp"
#include "../rendercontext.hpp"
#include <data.hpp>

RenderPass createTileRenderPass()
{
    return
    {
        AllocateFunction(nullptr),
        PreRenderFunction(nullptr),
        RenderFunction([](RenderContext& context, const GameData& data)
        {
            context.renderer.setViewport(data.defaultViewport);

            for(const auto& tileIter : data.worldTileMaps)
            {
                context.renderer.render(tileIter.second.background);
                context.renderer.render(tileIter.second.center);
            }
        }),
        ResizeFunction(nullptr),
        PostRenderFunction(nullptr),
        DeallocateFunction(nullptr),
    };
}
