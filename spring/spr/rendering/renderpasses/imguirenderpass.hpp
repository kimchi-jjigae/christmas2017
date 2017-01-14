#pragma once
#include <dpx/tableid.hpp>
#include <spr/data/tables.hpp>
#include <spr/rendering/renderpass.hpp>

namespace spr
{
spr::RenderPass createImguiRenderPass(dpx::TableId guiViewId, spr::Tables& tables);
}
