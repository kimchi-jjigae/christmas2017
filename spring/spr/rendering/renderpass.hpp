#pragma once
#include <functional>
#include <spr/glm.hpp>
#include <fea/rendering/renderer2d.hpp>

namespace spr
{
struct RenderContext;

using AllocateFunction   = std::function<void(fea::Renderer2D& renderer)>;
using PreRenderFunction  = std::function<void(RenderContext& context)>;
using RenderFunction     = std::function<void(RenderContext& context)>;
using ResizeFunction     = std::function<void(glm::ivec2 newSize)>;
using PostRenderFunction = std::function<void(RenderContext& context)>;
using DeallocateFunction = std::function<void()>;

struct RenderPass
{
    AllocateFunction   allocateFunction = nullptr;
    PreRenderFunction  preRenderFunction = nullptr;
    RenderFunction     renderFunction = nullptr;
    ResizeFunction     resizeFunction = nullptr;
    PostRenderFunction postRenderFunction = nullptr;
    DeallocateFunction deallocateFunction = nullptr;
};
}
