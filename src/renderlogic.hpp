//#pragma once
//#include <fea/render2d.hpp>
//#include <data.hpp>
//#include <imgui.h>
//
//class RenderLogic
//{
//    public:
//        RenderLogic(fea::Renderer2D& feaRenderer, GameData& data);
//        void frameStart();
//        void update();
//        void frameEnd();
//        void resize(glm::ivec2 newSize);
//    private:
//        void renderImGui(ImDrawData& drawData);
//        void updateEvilnessVisuals();
//        fea::Renderer2D& mFeaRenderer;
//        fea::RenderTarget mOverlayTarget;
//        fea::Quad mOverlayQuad;
//        fea::RepeatedQuad mFogOverlay;
//        fea::RepeatedQuad mNoiseOverlay;
//        fea::Animation mNoiseAnimation;
//        fea::Viewport mDefaultViewport;
//        fea::Viewport mOverlayViewport;
//        fea::Camera mWorldCamera;
//        fea::Camera mWorldOverlayCamera;
//        fea::Camera mGuiCamera;
//        GameData& mData;
//        int32_t mSinCounter;
//        fea::Animation mWizardAnimationUp;
//        fea::Animation mWizardAnimationDown;
//        fea::Animation mWizardAnimationLeft;
//        fea::Animation mWizardAnimationRight;
//        fea::AnimatedQuad mWizardQuad;
//};
