#pragma once
#include <fea/render2d.hpp>
#include <data.hpp>

class RenderLogic
{
    public:
        RenderLogic(fea::Renderer2D& feaRenderer, GameData& data);
        void frameStart();
        void update();
        void frameEnd();
        void resize(glm::ivec2 newSize);
    private:
        fea::Renderer2D& mFeaRenderer;
        GameData& mData;
};
