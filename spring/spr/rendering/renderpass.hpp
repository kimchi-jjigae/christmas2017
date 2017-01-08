#pragma once
#include <spr/glm.hpp>
#include <fea/rendering/renderer2d.hpp>

namespace spr
{
struct RenderContext;

template <typename ExtraData>
struct RenderPass
{
    using AllocateFunction   = void(*)(fea::Renderer2D& renderer, ExtraData& data);
    using PreRenderFunction  = void(*)(RenderContext& context, ExtraData& data);
    using RenderFunction     = void(*)(RenderContext& context, ExtraData& data);
    using ResizeFunction     = void(*)(glm::ivec2 newSize, ExtraData& data);
    using PostRenderFunction = void(*)(RenderContext& context, ExtraData& data);
    using DeallocateFunction = void(*)(ExtraData& data);

    AllocateFunction   allocateFunction = nullptr;
    PreRenderFunction  preRenderFunction = nullptr;
    RenderFunction     renderFunction = nullptr;
    ResizeFunction     resizeFunction = nullptr;
    PostRenderFunction postRenderFunction = nullptr;
    DeallocateFunction deallocateFunction = nullptr;
};
}
