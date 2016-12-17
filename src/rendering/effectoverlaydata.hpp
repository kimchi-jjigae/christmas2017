#pragma once
#include <fea/rendering/rendertarget.hpp>
#include <fea/rendering/repeatedquad.hpp>
#include <fea/rendering/animation.hpp>

struct EffectOverlayData
{
    fea::RenderTarget overlayTarget;
    fea::Quad overlayQuad;
    fea::RepeatedQuad fogOverlay;
    fea::RepeatedQuad noiseOverlay;
    fea::Animation noiseAnimation;
    int32_t sinCounter;
};
