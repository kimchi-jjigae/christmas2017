#pragma once
#include <dpx/tableid.hpp>
#include <spr/data/tables.hpp>

namespace spr
{
spr::RenderPass createDebugRenderPass(dpx::TableId view, spr::Tables& data);
}
