#pragma once
#include <spr/color/color.hpp>
#include <spr/rendering/spriterenderer.hpp>
#include <spr/rendering/imguirenderer.hpp>

struct GameData;

class RenderLogic
{
    public:
        RenderLogic(GameData& data);
        void frameStart(spr::Color clearColor = spr::Color::Black);
        void renderFrame();
        void resizeWindow(glm::ivec2 size);
    private:
        GameData& mData;
        dpx::TableId mShader;
        spr::SpriteRenderer mSpriteRenderer;
        spr::ImguiRenderer mImguiRenderer;
};
