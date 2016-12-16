#pragma once
#include <fea/render2d.hpp>
#include <glm.hpp>

struct RenderContext
{
    fea::Renderer2D& renderer;
    glm::ivec2 sceneSize;
};
