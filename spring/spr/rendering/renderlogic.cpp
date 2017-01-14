#include "renderlogic.hpp"
#include "rendercontext.hpp"
#include <imgui.h>
#include <spr/data/tables.hpp>
#include <spr/data/renderpassinstance.hpp>
#include <dpx/foreach.hpp>

namespace spr
{
RenderLogic::RenderLogic(fea::Renderer2D& feaRenderer, Tables& tables):
    mFeaRenderer(feaRenderer),
    mTables(tables)
{
}

void RenderLogic::frameStart()
{
    RenderContext context
    {
        mFeaRenderer,
    };

    mFeaRenderer.clear();

    sort(*mTables.tRenderPassInstance, [&] (size_t i, size_t j)
    {
        return mTables.tRenderPassInstance->data[i].priority < mTables.tRenderPassInstance->data[j].priority;
    });

    forEach([&](dpx::TableId id, const RenderPassInstance& renderPass)
    {
        auto preRenderFunction = renderPass.renderPass.preRenderFunction;
        if(preRenderFunction)
            preRenderFunction(context);
    }, *mTables.tRenderPassInstance);
}

void RenderLogic::update()
{
    RenderContext context
    {
        mFeaRenderer,
    };

    sort(*mTables.tRenderPassInstance, [&] (size_t i, size_t j)
    {
        return mTables.tRenderPassInstance->data[i].priority < mTables.tRenderPassInstance->data[j].priority;
    });

    forEach([&](dpx::TableId id, const RenderPassInstance& renderPass)
    {
        auto renderFunction = renderPass.renderPass.renderFunction;
        if(renderFunction)
            renderFunction(context);
    }, *mTables.tRenderPassInstance);
}

void RenderLogic::frameEnd()
{
    RenderContext context
    {
        mFeaRenderer,
    };

    sort(*mTables.tRenderPassInstance, [&] (size_t i, size_t j)
    {
        return mTables.tRenderPassInstance->data[i].priority < mTables.tRenderPassInstance->data[j].priority;
    });

    forEach([&](dpx::TableId id, const RenderPassInstance& renderPass)
    {
        auto postRenderFunction = renderPass.renderPass.postRenderFunction;
        if(postRenderFunction)
            postRenderFunction(context);
    }, *mTables.tRenderPassInstance);
}

void RenderLogic::resize(glm::ivec2 newSize)
{
    forEach([&](dpx::TableId id, const RenderPassInstance& renderPass)
    {
        auto resizeFunction = renderPass.renderPass.resizeFunction;
        if(resizeFunction)
            resizeFunction(newSize);
    }, *mTables.tRenderPassInstance);
}
}
