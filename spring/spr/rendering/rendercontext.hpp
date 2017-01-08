#pragma once
#include <fea/render2d.hpp>
#include <spr/glm.hpp>

namespace spr
{
struct RenderContext
{
    fea::Renderer2D& renderer;
    glm::ivec2 sceneSize;
};
}
