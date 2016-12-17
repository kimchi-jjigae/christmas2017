//#include "renderlogic.hpp"
//#include "debug.hpp"
//#include "drawables/linerect.hpp"
//#include "land/chunkutil.hpp"
//#include "land/goodness.hpp"
//
//RenderLogic::RenderLogic(fea::Renderer2D& feaRenderer, GameData& data):
//    mFeaRenderer(feaRenderer),
//    mData(data),
//{
//    mWizardAnimationUp = {{0,14}, {12, 14}, 2, 30};
//    mWizardAnimationDown = {{0,0}, {12, 14}, 2, 30};
//    mWizardAnimationLeft = {{0,28}, {12, 14}, 2, 30};
//    mWizardAnimationRight = {{0,42}, {12, 14}, 2, 30};
//    mWizardQuad.setSize(glm::ivec2{12,14} * 4);
//    mWizardQuad.setTexture(mData.wizardTexture);
//    mWizardQuad.setAnimation(mWizardAnimationUp);
//}
//
//void RenderLogic::frameStart()
//{
//    mFeaRenderer.clear();
//}
//
//void RenderLogic::update()
//{
//    mFeaRenderer.setViewport(mDefaultViewport);
//
//
//    if(mData.currentDirection == Direction::Up)
//        mWizardQuad.setAnimation(mWizardAnimationUp);
//    else if(mData.currentDirection == Direction::Down)
//        mWizardQuad.setAnimation(mWizardAnimationDown);
//    else if(mData.currentDirection == Direction::Left)
//        mWizardQuad.setAnimation(mWizardAnimationLeft);
//    else if(mData.currentDirection == Direction::Right)
//        mWizardQuad.setAnimation(mWizardAnimationRight);
//    mData.currentDirection = None;
//    mWizardQuad.tick();
//
//    mWizardQuad.setPosition(mData.cameraPosition);
//    mFeaRenderer.render(mWizardQuad);
//
//}
