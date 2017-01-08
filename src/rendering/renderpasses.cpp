#include "renderpasses.hpp"
#include "imguirenderpass.hpp"
#include "tilerenderpass.hpp"
#include "overlayrenderpass.hpp"
#include "spriterenderpass.hpp"
#include "debugrenderpass.hpp"

void registerRenderPasses(fea::Renderer2D& renderer, GameData& data)
{
    auto addRenderPass = [&] (int32_t order, spr::RenderPass<GameData> pass)
    {
        if(pass.allocateFunction)
            pass.allocateFunction(renderer, data);
        data.renderPasses.emplace(order, pass);
    };

    addRenderPass(50, createTileRenderPass());
    addRenderPass(60, createSpriteRenderPass());
    addRenderPass(70, createOverlayRenderPass());
    addRenderPass(80, createDebugRenderPass());
    addRenderPass(100, createImguiRenderPass());
}
