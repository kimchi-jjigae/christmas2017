#pragma once
#include <spr/glm.hpp>
#include <spr/color/color.hpp>
#include <spr/rendering/spriterenderer.hpp>
#include <spr/rendering/imguirenderer.hpp>
#include <spr/rendering/textrenderer.hpp>

struct GameData;

class RenderLogic
{
    public:
        struct Data
        {
            dpx::TableId mainShader = dpx::Null;
            dpx::TableId mainViewport = dpx::Null;
            dpx::TableId worldCamera = dpx::Null;
            dpx::TableId guiCamera = dpx::Null;
            bool reduceDebugTtl = true;
        };
        RenderLogic(Data& renderData, GameData& data);
        void frameStart(spr::Color clearColor = spr::Color::Black);
        void renderFrame();
        void resizeWindow(glm::ivec2 size);
    private:
        Data& mRenderData;
        GameData& mData;
        spr::SpriteRenderer mSpriteRenderer;
        spr::TextRenderer mTextRenderer;
        spr::ImguiRenderer mImguiRenderer;
};
