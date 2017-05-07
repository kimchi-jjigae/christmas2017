#include "inputlogic.hpp"
#include <gamedata.hpp>
#include <SDL2/SDL.h>

InputLogic::InputLogic(GameData& data):
    mData(data)
{
}

void InputLogic::update()
{
    mData.systemInput = {};
    mData.mouseClick = {};
    mData.mouseRelease = {};
    mData.mouseWheel = {};

    mData.startedPlayerActions.clear();
    mData.stoppedPlayerActions.clear();

    SDL_Event event;
    while(SDL_PollEvent(&event))
    {
        if(event.type == SDL_KEYDOWN)
        {
            //don't handle key repeats
            if(event.key.repeat != 0)
                continue;

            if(event.key.keysym.sym == SDLK_ESCAPE)
                mData.systemInput.quit = true;
            else if(event.key.keysym.sym == SDLK_w)
            {
                mData.startedPlayerActions.insert(PlayerAction::Throttle);
                mData.ongoingPlayerActions.insert(PlayerAction::Throttle);
            }
            else if(event.key.keysym.sym == SDLK_s)
            {
                mData.startedPlayerActions.insert(PlayerAction::Reverse);
                mData.ongoingPlayerActions.insert(PlayerAction::Reverse);
            }
            else if(event.key.keysym.sym == SDLK_a)
            {
                mData.startedPlayerActions.insert(PlayerAction::StrafeLeft);
                mData.ongoingPlayerActions.insert(PlayerAction::StrafeLeft);
            }
            else if(event.key.keysym.sym == SDLK_d)
            {
                mData.startedPlayerActions.insert(PlayerAction::StrafeRight);
                mData.ongoingPlayerActions.insert(PlayerAction::StrafeRight);
            }
            else if(event.key.keysym.sym == SDLK_LEFT)
            {
                mData.startedPlayerActions.insert(PlayerAction::TurnLeft);
                mData.ongoingPlayerActions.insert(PlayerAction::TurnLeft);
            }
            else if(event.key.keysym.sym == SDLK_RIGHT)
            {
                mData.startedPlayerActions.insert(PlayerAction::TurnRight);
                mData.ongoingPlayerActions.insert(PlayerAction::TurnRight);
            }
            else if(event.key.keysym.sym == SDLK_SPACE)
            {
                mData.startedPlayerActions.insert(PlayerAction::Fire);
                mData.ongoingPlayerActions.insert(PlayerAction::Fire);
            }
        }
        else if(event.type == SDL_KEYUP)
        {
            if(event.key.keysym.sym == SDLK_w)
            {
                mData.stoppedPlayerActions.insert(PlayerAction::Throttle);
                mData.ongoingPlayerActions.erase(PlayerAction::Throttle);
            }
            else if(event.key.keysym.sym == SDLK_s)
            {
                mData.stoppedPlayerActions.insert(PlayerAction::Reverse);
                mData.ongoingPlayerActions.erase(PlayerAction::Reverse);
            }
            else if(event.key.keysym.sym == SDLK_a)
            {
                mData.stoppedPlayerActions.insert(PlayerAction::StrafeLeft);
                mData.ongoingPlayerActions.erase(PlayerAction::StrafeLeft);
            }
            else if(event.key.keysym.sym == SDLK_d)
            {
                mData.stoppedPlayerActions.insert(PlayerAction::StrafeRight);
                mData.ongoingPlayerActions.erase(PlayerAction::StrafeRight);
            }
            else if(event.key.keysym.sym == SDLK_LEFT)
            {
                mData.stoppedPlayerActions.insert(PlayerAction::TurnLeft);
                mData.ongoingPlayerActions.erase(PlayerAction::TurnLeft);
            }
            else if(event.key.keysym.sym == SDLK_RIGHT)
            {
                mData.stoppedPlayerActions.insert(PlayerAction::TurnRight);
                mData.ongoingPlayerActions.erase(PlayerAction::TurnRight);
            }
            else if(event.key.keysym.sym == SDLK_SPACE)
            {
                mData.stoppedPlayerActions.insert(PlayerAction::Fire);
                mData.ongoingPlayerActions.erase(PlayerAction::Fire);
            }
            else if(event.key.keysym.sym == SDLK_o)
            {
                ++mData.advancePaused;
            }
            else if(event.key.keysym.sym == SDLK_p)
            {
                mData.paused = !mData.paused;
            }
            else if(event.key.keysym.sym == SDLK_COMMA)
            {
                mData.showDebugMenu = !mData.showDebugMenu;
            }
            else if(event.key.keysym.sym == SDLK_PERIOD)
            {
                mData.showProfiler = !mData.showProfiler;
            }
        }
        else if(event.type == SDL_QUIT)
        {
            mData.systemInput.quit = true;
        }
        else if(event.type == SDL_WINDOWEVENT)
        {
            if(event.window.event == SDL_WINDOWEVENT_RESIZED)
                mData.systemInput.resized = {event.window.data1, event.window.data2};
        }
        else if(event.type == SDL_MOUSEBUTTONDOWN)
        {
            MouseButton button = MouseButton::Left;

            if(event.button.button == SDL_BUTTON_LEFT)
                button = MouseButton::Left;
            else if(event.button.button == SDL_BUTTON_RIGHT)
                button = MouseButton::Right;
            else if(event.button.button == SDL_BUTTON_MIDDLE)
                button = MouseButton::Middle;

            mData.mouseClick = MouseClick{{event.button.x, event.button.y}, button};
        }
        else if(event.type == SDL_MOUSEBUTTONUP)
        {
            MouseButton button = MouseButton::Left;

            if(event.button.button == SDL_BUTTON_LEFT)
                button = MouseButton::Left;
            else if(event.button.button == SDL_BUTTON_RIGHT)
                button = MouseButton::Right;
            else if(event.button.button == SDL_BUTTON_MIDDLE)
                button = MouseButton::Middle;

            mData.mouseRelease = MouseRelease{{event.button.x, event.button.y}, button};
        }
        else if(event.type == SDL_MOUSEMOTION)
        {
            mData.mousePosition = glm::ivec2(event.motion.x, event.motion.y);
        }
        else if(event.type == SDL_MOUSEWHEEL)
        {
            mData.mouseWheel = event.wheel.y;
        }
    }
}
