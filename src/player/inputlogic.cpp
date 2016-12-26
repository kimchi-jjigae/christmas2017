#include "inputlogic.hpp"
#include "messages.hpp"
#include <data.hpp>

InputLogic::InputLogic(fea::MessageBus& bus, fea::InputHandler& handler, GameData& data):
    mLogic(handler),
    mBus(bus),
    mData(data),
    mMouseDown(false)
{
}

void InputLogic::update()
{
    mData.startedPlayerActions.clear();
    mData.stoppedPlayerActions.clear();
    fea::Event event;
    while(mLogic.pollEvent(event))
    {
        if(event.type == fea::Event::KEYPRESSED)
        {
            if(event.key.code == fea::Keyboard::ESCAPE)
                mBus.send(QuitMessage());
            else if(event.key.code == fea::Keyboard::W)
            {
                mData.startedPlayerActions.insert(PlayerAction::WalkUp);
                mData.ongoingPlayerActions.insert(PlayerAction::WalkUp);
            }
            else if(event.key.code == fea::Keyboard::S)
            {
                mData.startedPlayerActions.insert(PlayerAction::WalkDown);
                mData.ongoingPlayerActions.insert(PlayerAction::WalkDown);
            }
            else if(event.key.code == fea::Keyboard::A)
            {
                mData.startedPlayerActions.insert(PlayerAction::WalkLeft);
                mData.ongoingPlayerActions.insert(PlayerAction::WalkLeft);
            }
            else if(event.key.code == fea::Keyboard::D)
            {
                mData.startedPlayerActions.insert(PlayerAction::WalkRight);
                mData.ongoingPlayerActions.insert(PlayerAction::WalkRight);
            }
            else if(event.key.code == fea::Keyboard::H)
            {
                mData.startedPlayerActions.insert(PlayerAction::Staff);
                mData.ongoingPlayerActions.insert(PlayerAction::Staff);
            }

            mBus.send(KeyPressedMessage{event.key.code});
        }
        else if(event.type == fea::Event::KEYRELEASED)
        {
            if(event.key.code == fea::Keyboard::W)
            {
                mData.stoppedPlayerActions.insert(PlayerAction::WalkUp);
                mData.ongoingPlayerActions.erase(PlayerAction::WalkUp);
            }
            else if(event.key.code == fea::Keyboard::S)
            {
                mData.stoppedPlayerActions.insert(PlayerAction::WalkDown);
                mData.ongoingPlayerActions.erase(PlayerAction::WalkDown);
            }
            else if(event.key.code == fea::Keyboard::A)
            {
                mData.stoppedPlayerActions.insert(PlayerAction::WalkLeft);
                mData.ongoingPlayerActions.erase(PlayerAction::WalkLeft);
            }
            else if(event.key.code == fea::Keyboard::D)
            {
                mData.stoppedPlayerActions.insert(PlayerAction::WalkRight);
                mData.ongoingPlayerActions.erase(PlayerAction::WalkRight);
            }
            else if(event.key.code == fea::Keyboard::H)
            {
                mData.stoppedPlayerActions.insert(PlayerAction::Staff);
                mData.ongoingPlayerActions.erase(PlayerAction::Staff);
            }
        }
        else if(event.type == fea::Event::CLOSED)
        {
            mBus.send(QuitMessage());
        }
        else if(event.type == fea::Event::RESIZED)
        {
            mBus.send(ResizeMessage{{event.size.width, event.size.height}});
        }
        else if(event.type == fea::Event::MOUSEBUTTONPRESSED)
        {
            mMouseDown = true;
            mBus.send(MouseClickMessage{event.mouseButton.button, {event.mouseButton.x, event.mouseButton.y}});
        }
        else if(event.type == fea::Event::MOUSEBUTTONRELEASED)
        {
            mMouseDown = false;
            mBus.send(MouseReleaseMessage{event.mouseButton.button, {event.mouseButton.x, event.mouseButton.y}});
        }
        else if(event.type == fea::Event::MOUSEMOVED)
        {
            mBus.send(MouseMoveMessage{{event.mouseMove.x, event.mouseMove.y}, mMouseDown});
        }
        else if(event.type == fea::Event::MOUSEWHEELMOVED)
        {
            mBus.send(MouseWheelMessage{event.mouseWheel.delta});
        }
    }
}
