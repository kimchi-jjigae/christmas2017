#pragma once
#include <fea/render2d.hpp>

namespace spr
{
struct Tables;

class RenderLogic
{
    public:
        RenderLogic(fea::Renderer2D& feaRenderer, Tables& tables);
        void frameStart();
        void update();
        void frameEnd();
        void resize(glm::ivec2 newSize);
    private:
        fea::Renderer2D& mFeaRenderer;
        Tables& mTables;
};
}
