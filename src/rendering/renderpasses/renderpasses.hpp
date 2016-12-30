#pragma once

namespace fea
{
    class Renderer2D;
}

struct GameData;

void registerRenderPasses(fea::Renderer2D& renderer, GameData& data);
