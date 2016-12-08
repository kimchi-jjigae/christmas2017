#pragma once
#include <array>
#include <fea/rendering/texture.hpp>
#include <fea/rendering/quad.hpp>
#include <fea/rendering/repeatedquad.hpp>

struct ChunkViewData
{
    std::array<fea::Texture, 4> overlayMasks;
    fea::Quad overlayQuad;
};
