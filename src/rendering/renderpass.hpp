#pragma once
#include <glm.hpp>

struct RenderContext;
struct GameData;

using AllocateFunction   = void(*)(RenderContext& context, const GameData& data);
using PreRenderFunction  = void(*)(RenderContext& context, const GameData& data);
using RenderFunction     = void(*)(RenderContext& context, const GameData& data);
using ResizeFunction     = void(*)(glm::ivec2 newSize, GameData& data);
using PostRenderFunction = void(*)(RenderContext& context, const GameData& data);
using DeallocateFunction = void(*)(RenderContext& context, const GameData& data);

struct RenderPass
{
    AllocateFunction   allocateFunction = nullptr;
    PreRenderFunction  preRenderFunction = nullptr;
    RenderFunction     renderFunction = nullptr;
    ResizeFunction     resizeFunction = nullptr;
    PostRenderFunction postRenderFunction = nullptr;
    DeallocateFunction deallocateFunction = nullptr;
};
