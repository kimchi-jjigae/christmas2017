#include "spriterenderpass.hpp"
#include "../rendercontext.hpp"
#include "../../debugrenderer.hpp"
#include <data.hpp>

RenderPass createDebugRenderPass()
{
    return
    {
        AllocateFunction([](fea::Renderer2D& renderer, GameData& data)
        {
            DRen::initialize(renderer, data.worldCamera);
        }),
        PreRenderFunction(nullptr),
        RenderFunction([](RenderContext& context, GameData& data)
        {
            DRen::setCamera(data.worldCamera);
            DRen::flush();
        }),
        ResizeFunction(nullptr),
        PostRenderFunction(nullptr),
        DeallocateFunction(nullptr),
    };
}
