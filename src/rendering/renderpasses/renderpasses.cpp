#include "renderpasses.hpp"
#include "imguirenderpass.hpp"
#include "tilerenderpass.hpp"
#include "overlayrenderpass.hpp"
#include "spriterenderpass.hpp"
#include <data.hpp>

void registerRenderPasses(GameData& data)
{
    auto addRenderPass = [&] (int32_t order, RenderPass pass)
    {
        if(pass.allocateFunction)
            pass.allocateFunction(data);
        data.renderPasses.emplace(order, pass);
    };

    addRenderPass(50, createTileRenderPass());
    addRenderPass(60, createSpriteRenderPass());
    addRenderPass(70, createOverlayRenderPass());
    addRenderPass(100, createImguiRenderPass());
}
