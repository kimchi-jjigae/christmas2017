#pragma once
#include <glm.hpp>
#include <fea/rendering/renderer2d.hpp>

struct RenderContext;
struct GameData;

using AllocateFunction   = void(*)(fea::Renderer2D& renderer, GameData& data);
using PreRenderFunction  = void(*)(RenderContext& context, GameData& data);
using RenderFunction     = void(*)(RenderContext& context, GameData& data);
using ResizeFunction     = void(*)(glm::ivec2 newSize, GameData& data);
using PostRenderFunction = void(*)(RenderContext& context, GameData& data);
using DeallocateFunction = void(*)(GameData& data);

struct RenderPass
{
    AllocateFunction   allocateFunction = nullptr;
    PreRenderFunction  preRenderFunction = nullptr;
    RenderFunction     renderFunction = nullptr;
    ResizeFunction     resizeFunction = nullptr;
    PostRenderFunction postRenderFunction = nullptr;
    DeallocateFunction deallocateFunction = nullptr;
};
