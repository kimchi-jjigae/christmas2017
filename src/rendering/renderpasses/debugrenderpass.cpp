#include "spriterenderpass.hpp"
#include "../rendercontext.hpp"
#include <spr/debug/debugrenderer.hpp>
#include <data.hpp>

RenderPass createDebugRenderPass()
{
    return
    {
        AllocateFunction([](fea::Renderer2D& renderer, GameData& data)
        {
            spr::DRen::initialize(renderer, data.worldCamera);
        }),
        PreRenderFunction(nullptr),
        RenderFunction([](RenderContext& context, GameData& data)
        {
            spr::DRen::setCamera(data.worldCamera);
            spr::DRen::flush();
        }),
        ResizeFunction(nullptr),
        PostRenderFunction(nullptr),
        DeallocateFunction(nullptr),
    };
}
