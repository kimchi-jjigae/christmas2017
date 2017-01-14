#include "spriterenderpass.hpp"
#include <spr/data/view.hpp>
#include <spr/debug/debugrenderer.hpp>

namespace spr
{
spr::RenderPass createDebugRenderPass(dpx::TableId view, spr::Tables& data)
{
    return
    {
        spr::AllocateFunction([view, &data](fea::Renderer2D& renderer)
        {
            spr::DRen::initialize(renderer, get(view, *data.tView).viewport.getCamera());
        }),
        spr::PreRenderFunction(nullptr),
        spr::RenderFunction([view, &data](spr::RenderContext& context)
        {
            spr::DRen::setCamera(get(view, *data.tView).viewport.getCamera());
            spr::DRen::flush();
        }),
        spr::ResizeFunction(nullptr),
        spr::PostRenderFunction(nullptr),
        spr::DeallocateFunction(nullptr),
    };
}
}
