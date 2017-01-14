#pragma once
#include <dpx/tableid.hpp>
#include <spr/rendering/renderpass.hpp>
#include <spr/data/tables.hpp>

namespace spr
{
spr::RenderPass createSpriteRenderPass(dpx::TableId viewId, spr::Tables& tables);
}
