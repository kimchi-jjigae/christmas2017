#include "renderpasses.hpp"
#include "imguirenderpass.hpp"
#include "tilerenderpass.hpp"
#include <data.hpp>

void registerRenderPasses(GameData& data)
{
    data.renderPasses.emplace(50, createTileRenderPass());
    data.renderPasses.emplace(100, createImguiRenderPass());
}
