#include "imguirenderpass.hpp"
#include <spr/rendering/rendercontext.hpp>
#include <spr/rendering/drawables/imguidrawable.hpp>
#include <imgui.h>

spr::RenderPass<GameData> createImguiRenderPass()
{
    return
    {
        //maybe allocate gui    
        spr::RenderPass<GameData>::AllocateFunction(nullptr),
        spr::RenderPass<GameData>::PreRenderFunction([](spr::RenderContext& context, GameData& data)
        {
            ImGui::NewFrame();
        }),
        spr::RenderPass<GameData>::RenderFunction([](spr::RenderContext& context, GameData& data)
        {
            ImGui::Render();
            ImDrawData& drawData = *ImGui::GetDrawData();

            context.renderer.setViewport(data.guiViewport);
            //context.renderer.getViewport().setCamera(mGuiCamera); NOTE: fix GUI CAMERA
           
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
                        spr::ImGuiDrawable drawable(vtx_buffer, idx_buffer, static_cast<int32_t>(pcmd->ElemCount), pcmd->TextureId);
                        context.renderer.render(drawable);
                    }
                    idx_buffer += pcmd->ElemCount;
                }
            }
            
            glDisable(GL_SCISSOR_TEST);
        }),
        spr::RenderPass<GameData>::ResizeFunction([](glm::ivec2 newSize, GameData& data)
        {
            data.guiCamera.setPosition(newSize / 2);
        }),
        spr::RenderPass<GameData>::PostRenderFunction(nullptr),
        //deallocate gui
        spr::RenderPass<GameData>::DeallocateFunction(nullptr),
    };
}
