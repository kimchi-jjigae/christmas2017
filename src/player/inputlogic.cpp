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
                mData.startedPlayerActions.insert(PlayerAction::Up);
                mData.ongoingPlayerActions.insert(PlayerAction::Up);
            }
            else if(event.key.keysym.sym == SDLK_s)
            {
                mData.startedPlayerActions.insert(PlayerAction::Down);
                mData.ongoingPlayerActions.insert(PlayerAction::Down);
            }
            else if(event.key.keysym.sym == SDLK_a)
            {
                mData.startedPlayerActions.insert(PlayerAction::Left);
                mData.ongoingPlayerActions.insert(PlayerAction::Left);
            }
            else if(event.key.keysym.sym == SDLK_d)
            {
                mData.startedPlayerActions.insert(PlayerAction::Right);
                mData.ongoingPlayerActions.insert(PlayerAction::Right);
            }
            else if(event.key.keysym.sym == SDLK_UP)
            {
                mData.startedPlayerActions.insert(PlayerAction::TurnLeft);
                mData.ongoingPlayerActions.insert(PlayerAction::TurnLeft);
            }
            else if(event.key.keysym.sym == SDLK_DOWN)
            {
                mData.startedPlayerActions.insert(PlayerAction::TurnLeft);
                mData.ongoingPlayerActions.insert(PlayerAction::TurnLeft);
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
                mData.startedPlayerActions.insert(PlayerAction::Punch);
                mData.ongoingPlayerActions.insert(PlayerAction::Punch);
            }
        }
        else if(event.type == SDL_KEYUP)
        {
            if(event.key.keysym.sym == SDLK_w)
            {
                mData.stoppedPlayerActions.insert(PlayerAction::Up);
                mData.ongoingPlayerActions.erase(PlayerAction::Up);
            }
            else if(event.key.keysym.sym == SDLK_s)
            {
                mData.stoppedPlayerActions.insert(PlayerAction::Down);
                mData.ongoingPlayerActions.erase(PlayerAction::Down);
            }
            else if(event.key.keysym.sym == SDLK_a)
            {
                mData.stoppedPlayerActions.insert(PlayerAction::Left);
                mData.ongoingPlayerActions.erase(PlayerAction::Left);
            }
            else if(event.key.keysym.sym == SDLK_d)
            {
                mData.stoppedPlayerActions.insert(PlayerAction::Right);
                mData.ongoingPlayerActions.erase(PlayerAction::Right);
            }
            else if(event.key.keysym.sym == SDLK_UP)
            {
                mData.stoppedPlayerActions.insert(PlayerAction::TurnLeft);
                mData.ongoingPlayerActions.erase(PlayerAction::TurnLeft);
            }
            else if(event.key.keysym.sym == SDLK_DOWN)
            {
                mData.stoppedPlayerActions.insert(PlayerAction::TurnLeft);
                mData.ongoingPlayerActions.erase(PlayerAction::TurnLeft);
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
                mData.stoppedPlayerActions.insert(PlayerAction::Punch);
                mData.ongoingPlayerActions.erase(PlayerAction::Punch);
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
                mData.showTables = !mData.showTables;
            }
            else if(event.key.keysym.sym == SDLK_PERIOD)
            {
                mData.showProfiler = !mData.showProfiler;
            }
            else if(event.key.keysym.sym == SDLK_SLASH)
            {
                mData.showDebugMenu = !mData.showDebugMenu;
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
