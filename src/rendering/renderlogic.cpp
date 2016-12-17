#include "renderlogic.hpp"
#include "rendercontext.hpp"
#include <imgui.h>

RenderLogic::RenderLogic(fea::Renderer2D& feaRenderer, GameData& data):
    mFeaRenderer(feaRenderer),
    mData(data)
{
    mData.defaultViewport = feaRenderer.getViewport();
    mData.guiViewport = feaRenderer.getViewport();
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

    //setup position and zoom
    mData.worldCamera.setPosition(mData.cameraPosition);
    mData.worldCamera.setZoom({mData.zoom, mData.zoom});
    mData.defaultViewport.setCamera(mData.worldCamera);
    mData.guiViewport.setCamera(mData.guiCamera);
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

    mData.defaultViewport = fea::Viewport(newSize, {}, {});
    mData.guiViewport = fea::Viewport(newSize, {}, {});
}
