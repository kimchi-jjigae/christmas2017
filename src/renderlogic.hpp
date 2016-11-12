#pragma once
#include <fea/render2d.hpp>
#include <data.hpp>
#include <imgui.h>

class RenderLogic
{
    public:
        RenderLogic(fea::Renderer2D& feaRenderer, const GameData& data);
        void frameStart();
        void update();
        void frameEnd();
    private:
        void renderImGui(ImDrawData& drawData);
        fea::Renderer2D& mFeaRenderer;
        const GameData& mData;
};
