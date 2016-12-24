#pragma once
#include <fea/util.hpp>
#include <fea/userinterface.hpp>

struct GameData;

class InputLogic
{
    public:
        InputLogic(fea::MessageBus& bus, fea::InputHandler& handler, GameData& data);
        void update();
    private:
        fea::InputHandler& mLogic;
        fea::MessageBus& mBus;
        GameData& mData;

        bool mMouseDown;
};
