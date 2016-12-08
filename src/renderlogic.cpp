#include "renderlogic.hpp"
#include "debug.hpp"
#include "drawables/linerect.hpp"
#include "drawables/imguidrawable.hpp"
#include "renderingutil.hpp"
#include "land/chunkutil.hpp"
#include "land/goodness.hpp"

RenderLogic::RenderLogic(fea::Renderer2D& feaRenderer, GameData& data):
    mFeaRenderer(feaRenderer),
    mData(data),
    mSinCounter(0)
{
    mOverlayTarget.create({2048, 2048});
    mOverlayQuad.setSize({2048, 2048});
    mOverlayQuad.setTexture(mOverlayTarget.getTexture());
    mOverlayQuad.setVFlip(true);

    mDefaultViewport = mFeaRenderer.getViewport();
    mOverlayViewport = fea::Viewport({2048, 2048}, {}, fea::Camera{});
    
    mNoiseAnimation = {{0,0}, {32, 32}, 4, 4};
    mNoiseOverlay.setSize({130000.0f, 130000.0f});
    mNoiseOverlay.setPosition(-mNoiseOverlay.getSize() / 2.0f);
    mNoiseOverlay.setTexture(mData.noiseTexture);
    mNoiseOverlay.setAnimation(mNoiseAnimation);
    mNoiseOverlay.setTileSize(glm::ivec2{64, 64});
    mNoiseOverlay.setParallax({0.0f, 0.0f});
    mFogOverlay.setSize({130000.0f, 130000.0f});
    mFogOverlay.setPosition(-mFogOverlay.getSize() / 2.0f);
    mFogOverlay.setTexture(mData.fogTexture);
    mFogOverlay.setTileSize(glm::ivec2{256, 256});
    mFogOverlay.setScrollSpeed({0.00001f, 0.0f});
    mFogOverlay.setParallax({0.1f, 0.1f});
}

void RenderLogic::frameStart()
{
    mFeaRenderer.clear();
    mFeaRenderer.clear(mOverlayTarget, fea::Color::Transparent);
    ImGui::NewFrame();
}

void RenderLogic::update()
{
    for(const auto& coordinate : mData.chunksToPutInView)
    {
        TH_ASSERT(mData.chunksInView.count(coordinate) == 0, "Was about to emplace chunk in view, but it was already there " << coordinate);
        setupOverlay(coordinate, mData.chunksInView.emplace(coordinate, ChunkViewData{std::move(mData.chunkOverlayPool.back()), {}}).first->second, mData.worldChunks.at(coordinate), mData);
        mData.chunkOverlayPool.pop_back();
    }
    mData.chunksToPutInView.clear();

    for(const auto& coordinate : mData.chunksThatLeftView)
    {
        TH_ASSERT(mData.chunksInView.count(coordinate) != 0, "Was about to erase chunk from view, but it was not there " << coordinate);
        mData.chunkOverlayPool.emplace_back(std::move(mData.chunksInView.at(coordinate).overlayMasks));
        mData.chunksInView.erase(coordinate);
    }
    mData.chunksThatLeftView.clear();

    updateEvilnessVisuals();


    mWorldCamera.setPosition(mData.cameraPosition);
    mWorldCamera.setZoom({mData.zoom, mData.zoom});
    mDefaultViewport.setCamera(mWorldCamera);
    mWorldOverlayCamera.setPosition(mData.cameraPosition);// - glm::ivec2(-342, 0));
    mWorldOverlayCamera.setZoom({1, mData.zoom});
    mFeaRenderer.setViewport(mDefaultViewport);

    for(const auto& tileIter : mData.worldTileMaps)
    {
        mFeaRenderer.render(tileIter.second.background);
        mFeaRenderer.render(tileIter.second.center);
    }

    mFeaRenderer.render(mFogOverlay);
    mFeaRenderer.render(mNoiseOverlay);
    mFogOverlay.tick();
    mNoiseOverlay.tick();

    mOverlayViewport.setCamera(mWorldOverlayCamera);
    mFeaRenderer.setViewport(mOverlayViewport);
    //overlay stuff
    for(auto& overlays : mData.chunksInView)
    {
        mFeaRenderer.setBlendMode(fea::ADD);
        mFeaRenderer.render(overlays.second.overlayQuad, mOverlayTarget);
    }

    mFeaRenderer.setViewport(mDefaultViewport);
    mOverlayQuad.setPosition(mData.cameraPosition - glm::ivec2(1024.0f, 1024.0f));
    mFeaRenderer.setBlendMode(fea::MULTIPLY);
    mFeaRenderer.render(mOverlayQuad);
    mFeaRenderer.setBlendMode(fea::ALPHA);
}

void RenderLogic::frameEnd()
{
    ImGui::Render();
    renderImGui(*ImGui::GetDrawData());
}

void RenderLogic::resize(glm::ivec2 newSize)
{
    mDefaultViewport = fea::Viewport(newSize, {}, {});
    mGuiCamera.setPosition(newSize / 2);
    exit(4);
}

void RenderLogic::renderImGui(ImDrawData& drawData)
{
    mFeaRenderer.getViewport().setCamera(mGuiCamera);
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

void RenderLogic::updateEvilnessVisuals()
{
    glm::ivec2 cameraTile = worldToTile(mData.cameraPosition);
    glm::ivec2 cameraChunk = tileToChunk(cameraTile);
    int32_t goodnessAmount = mData.worldChunks.at(cameraChunk).tiles[tileIndex(tileToChunkTile(cameraTile))].goodness;
    GoodnessLevel goodnessLevel = goodnessAmountLevel(goodnessAmount);
    int32_t evilAmount = goodnessLevelAmount(GoodnessLevel::Evil, goodnessAmount);
    int32_t dyingAmount = goodnessLevelAmount(GoodnessLevel::Dying, goodnessAmount);
    int32_t corruptAmount = goodnessLevelAmount(GoodnessLevel::Corrupt, goodnessAmount);
    int32_t goodAmount = goodnessLevelAmount(GoodnessLevel::Good, goodnessAmount);

    mSinCounter += 4000;
    if(mSinCounter > 314159)
        mSinCounter = 0;

    float sinInput = mSinCounter / 100000.0f;
    float sinOut = std::sin(sinInput);
    mNoiseOverlay.setColor({static_cast<int32_t>(255 * std::fabs(sinOut)), 0, 0, 255});
    mNoiseOverlay.setOpacity(std::max(0.0f, evilAmount / 100.0f - 0.15f));
    mFogOverlay.setOpacity(std::max(0.0f, dyingAmount / 100.0f - 0.15f));
}
