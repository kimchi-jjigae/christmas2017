#include "renderpasses.hpp"
#include "imguirenderpass.hpp"
#include <data.hpp>

void registerRenderPasses(GameData& data)
{
    data.renderPasses.emplace(100, createImguiRenderPass());
}
