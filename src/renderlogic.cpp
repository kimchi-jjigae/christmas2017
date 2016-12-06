#include "renderlogic.hpp"
#include "debug.hpp"
#include "drawables/linerect.hpp"
#include "drawables/imguidrawable.hpp"

RenderLogic::RenderLogic(fea::Renderer2D& feaRenderer, const GameData& data):
    mFeaRenderer(feaRenderer),
    mData(data)
{
}

void RenderLogic::frameStart()
{
    mFeaRenderer.clear();
    ImGui::NewFrame();
}

void RenderLogic::update()
{
    for(const auto& tileIter : mData.worldTileMaps)
    {
        mFeaRenderer.render(tileIter.second);
    }
}

void RenderLogic::frameEnd()
{
    ImGui::Render();
    renderImGui(*ImGui::GetDrawData());
}

void RenderLogic::renderImGui(ImDrawData& drawData)
{
    // Avoid rendering when minimized, scale coordinates for retina displays (screen coordinates != framebuffer coordinates)
    ImGuiIO& io = ImGui::GetIO();
    int fb_width = (int)(io.DisplaySize.x * io.DisplayFramebufferScale.x);
    int fb_height = (int)(io.DisplaySize.y * io.DisplayFramebufferScale.y);
    if (fb_width == 0 || fb_height == 0)
        return;
    drawData.ScaleClipRects(io.DisplayFramebufferScale);

    glEnable(GL_SCISSOR_TEST);
   
    //// Render command lists
    for (int n = 0; n < drawData.CmdListsCount; n++)
    {
        const ImDrawList* cmd_list = drawData.CmdLists[n];
        const unsigned char* vtx_buffer = (const unsigned char*)&cmd_list->VtxBuffer.front();
        const ImDrawIdx* idx_buffer = &cmd_list->IdxBuffer.front();

        for (int cmd_i = 0; cmd_i < cmd_list->CmdBuffer.size(); cmd_i++)
        {
            const ImDrawCmd* pcmd = &cmd_list->CmdBuffer[cmd_i];
            if (pcmd->UserCallback)
            {
                pcmd->UserCallback(cmd_list, pcmd);
            }
            else
            {
                glScissor((int)pcmd->ClipRect.x, (int)(fb_height - pcmd->ClipRect.w), (int)(pcmd->ClipRect.z - pcmd->ClipRect.x), (int)(pcmd->ClipRect.w - pcmd->ClipRect.y));
                ImGuiDrawable drawable(vtx_buffer, idx_buffer, static_cast<int32_t>(pcmd->ElemCount), pcmd->TextureId);
                mFeaRenderer.render(drawable);
            }
            idx_buffer += pcmd->ElemCount;
        }
    }

    glDisable(GL_SCISSOR_TEST);
}
