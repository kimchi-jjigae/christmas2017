#include "renderpasses.hpp"
#include <spr/rendering/renderpasses/imguirenderpass.hpp>
#include <spr/rendering/renderpasses/spriterenderpass.hpp>
#include <spr/rendering/renderpasses/debugrenderpass.hpp>
#include "overlayrenderpass.hpp"
#include "tilerenderpass.hpp"
#include <spr/data/view.hpp>
#include <spr/data/renderpassinstance.hpp>
#include <gamedata.hpp>

void registerRenderPasses(fea::Renderer2D& renderer, GameData& data)
{
    auto addRenderPass = [&] (int32_t order, spr::RenderPass pass)
    {
        if(pass.allocateFunction)
            pass.allocateFunction(renderer);
        insert(spr::RenderPassInstance{pass, order}, *data.spr.tRenderPassInstance);
    };

    auto defaultViewport = fea::Viewport(initialScreenSize, {0, 0}, fea::Camera(static_cast<glm::vec2>(initialScreenSize / 2)));

    data.worldView = insert(spr::View{defaultViewport}, *data.spr.tView).id;
    data.guiView = insert(spr::View{defaultViewport}, *data.spr.tView).id;

    addRenderPass(50, createTileRenderPass(data));
    addRenderPass(60, createSpriteRenderPass(data.worldView, data.spr));
    addRenderPass(70, createOverlayRenderPass(data));
    addRenderPass(80, createDebugRenderPass(data.worldView, data.spr));
    addRenderPass(100, createImguiRenderPass(data.guiView, data.spr));
}
