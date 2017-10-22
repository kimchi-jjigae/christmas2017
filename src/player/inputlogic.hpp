#pragma once
#include <cstdint>

struct GameData;

class InputLogic
{
    public:
        InputLogic(GameData& data);
        void update();
        void clearStartedAndStopped();
        void mapImguiKeys(int32_t* keyMap);
    private:
        void handleImguiInput(const union SDL_Event& event);
        GameData& mData;
};
