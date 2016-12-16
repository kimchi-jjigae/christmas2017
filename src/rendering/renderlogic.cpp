#include "renderlogic.hpp"
#include "rendercontext.hpp"
#include <imgui.h>

RenderLogic::RenderLogic(fea::Renderer2D& feaRenderer, GameData& data):
    mFeaRenderer(feaRenderer),
    mData(data)
{
}

void RenderLogic::frameStart()
{
    RenderContext context
    {
        mFeaRenderer,
        mData.screenSize,
    };

    mFeaRenderer.clear();

    for(auto iter : mData.renderPasses)
    {
        auto preRenderFunction = iter.second.preRenderFunction;
        if(preRenderFunction)
            preRenderFunction(context, mData);
    }
}

void RenderLogic::update()
{
    RenderContext context
    {
        mFeaRenderer,
        mData.screenSize,
    };

    for(auto iter : mData.renderPasses)
    {
        auto renderFunction = iter.second.renderFunction;
        if(renderFunction)
            renderFunction(context, mData);
    }
}

void RenderLogic::frameEnd()
{
    RenderContext context
    {
        mFeaRenderer,
        mData.screenSize,
    };

    for(auto iter : mData.renderPasses)
    {
        auto postRenderFunction = iter.second.postRenderFunction;
        if(postRenderFunction)
            postRenderFunction(context, mData);
    }
}

void RenderLogic::resize(glm::ivec2 newSize)
{
    for(auto iter : mData.renderPasses)
    {
        auto resizeFunction = iter.second.resizeFunction;
        if(resizeFunction)
            resizeFunction(newSize, mData);
    }
    //mDefaultViewport = fea::Viewport(newSize, {}, {});
}
