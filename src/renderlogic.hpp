#pragma once
#include <fea/render2d.hpp>
#include <data.hpp>
#include <imgui.h>

class RenderLogic
{
    public:
        RenderLogic(fea::Renderer2D& feaRenderer, GameData& data);
        void frameStart();
        void update();
        void frameEnd();
        void resize(glm::ivec2 newSize);
    private:
        void renderImGui(ImDrawData& drawData);
        fea::Renderer2D& mFeaRenderer;
        fea::RenderTarget mOverlayTarget;
        fea::Quad mOverlayQuad;
        fea::Viewport mDefaultViewport;
        fea::Viewport mOverlayViewport;
        fea::Camera mWorldCamera;
        fea::Camera mWorldOverlayCamera;
        fea::Camera mGuiCamera;
        GameData& mData;
};
