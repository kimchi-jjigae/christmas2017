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
        ImGuiIO& imgui = ImGui::GetIO();

        //system input
        if(event.type == SDL_QUIT)
        {
            mData.systemInput.quit = true;
        }
        else if(event.type == SDL_WINDOWEVENT)
        {
            if(event.window.event == SDL_WINDOWEVENT_RESIZED)
            {
                mData.systemInput.resized = {event.window.data1, event.window.data2};
                imgui.DisplaySize.x = static_cast<float>(event.window.data1);
                imgui.DisplaySize.y = static_cast<float>(event.window.data2);
            }
        }

        handleImguiInput(event);

        //game input. not going to be triggered if imgui wants focus
        if(event.type == SDL_KEYDOWN && !imgui.WantCaptureKeyboard)
        {
            //don't handle key repeats
            if(event.key.repeat != 0)
                continue;

            if(event.key.keysym.sym == SDLK_ESCAPE)
            {
                mData.systemInput.quit = true;
            }
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
                mData.startedPlayerActions.insert(PlayerAction::Up);
                mData.ongoingPlayerActions.insert(PlayerAction::Up);
            }
            else if(event.key.keysym.sym == SDLK_DOWN)
            {
                mData.startedPlayerActions.insert(PlayerAction::Down);
                mData.ongoingPlayerActions.insert(PlayerAction::Down);
            }
            else if(event.key.keysym.sym == SDLK_LEFT)
            {
                mData.startedPlayerActions.insert(PlayerAction::Left);
                mData.ongoingPlayerActions.insert(PlayerAction::Left);
            }
            else if(event.key.keysym.sym == SDLK_RIGHT)
            {
                mData.startedPlayerActions.insert(PlayerAction::Right);
                mData.ongoingPlayerActions.insert(PlayerAction::Right);
            }
            else if(event.key.keysym.sym == SDLK_SPACE)
            {
                mData.startedPlayerActions.insert(PlayerAction::LoadPunch);
                mData.ongoingPlayerActions.insert(PlayerAction::LoadPunch);
            }
        }
        else if(event.type == SDL_KEYUP && !imgui.WantCaptureKeyboard)
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
                mData.stoppedPlayerActions.insert(PlayerAction::Up);
                mData.ongoingPlayerActions.erase(PlayerAction::Up);
            }
            else if(event.key.keysym.sym == SDLK_DOWN)
            {
                mData.stoppedPlayerActions.insert(PlayerAction::Down);
                mData.ongoingPlayerActions.erase(PlayerAction::Down);
            }
            else if(event.key.keysym.sym == SDLK_LEFT)
            {
                mData.stoppedPlayerActions.insert(PlayerAction::Left);
                mData.ongoingPlayerActions.erase(PlayerAction::Left);
            }
            else if(event.key.keysym.sym == SDLK_RIGHT)
            {
                mData.stoppedPlayerActions.insert(PlayerAction::Right);
                mData.ongoingPlayerActions.erase(PlayerAction::Right);
            }
            else if(event.key.keysym.sym == SDLK_SPACE)
            {
                mData.stoppedPlayerActions.insert(PlayerAction::LoadPunch);
                mData.ongoingPlayerActions.erase(PlayerAction::LoadPunch);
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
        else if(event.type == SDL_MOUSEBUTTONDOWN && !imgui.WantCaptureMouse)
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
        else if(event.type == SDL_MOUSEBUTTONUP && !imgui.WantCaptureMouse)
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
        else if(event.type == SDL_MOUSEMOTION && !imgui.WantCaptureMouse)
        {
            mData.mousePosition = glm::ivec2(event.motion.x, event.motion.y);
        }
        else if(event.type == SDL_MOUSEWHEEL && !imgui.WantCaptureMouse)
        {
            mData.mouseWheel = event.wheel.y;
        }
    }
}

void InputLogic::clearStartedAndStopped()
{
    mData.startedPlayerActions.clear();
    mData.stoppedPlayerActions.clear();
}

void InputLogic::mapImguiKeys(int32_t* keyMap)
{
    keyMap[ImGuiKey_Tab] = SDL_SCANCODE_TAB;       // for tabbing through fields
    keyMap[ImGuiKey_LeftArrow] = SDL_SCANCODE_LEFT; // for text edit
    keyMap[ImGuiKey_RightArrow] = SDL_SCANCODE_RIGHT;// for text edit
    keyMap[ImGuiKey_UpArrow] = SDL_SCANCODE_UP;   // for text edit
    keyMap[ImGuiKey_DownArrow] = SDL_SCANCODE_DOWN; // for text edit
    keyMap[ImGuiKey_PageUp] = SDL_SCANCODE_PAGEUP;
    keyMap[ImGuiKey_PageDown] = SDL_SCANCODE_PAGEDOWN;
    keyMap[ImGuiKey_Home] = SDL_SCANCODE_HOME;      // for text edit
    keyMap[ImGuiKey_End] = SDL_SCANCODE_END;       // for text edit
    keyMap[ImGuiKey_Delete] = SDL_SCANCODE_DELETE;    // for text edit
    keyMap[ImGuiKey_Backspace] = SDL_SCANCODE_BACKSPACE; // for text edit
    keyMap[ImGuiKey_Enter] = SDL_SCANCODE_RETURN;     // for text edit
    keyMap[ImGuiKey_Escape] = SDL_SCANCODE_ESCAPE;    // for text edit
    keyMap[ImGuiKey_A] = SDL_SCANCODE_A;         // for text edit CTRL+A: select all
    keyMap[ImGuiKey_C] = SDL_SCANCODE_C;         // for text edit CTRL+C: copy
    keyMap[ImGuiKey_V] = SDL_SCANCODE_V;         // for text edit CTRL+V: paste
    keyMap[ImGuiKey_X] = SDL_SCANCODE_X;         // for text edit CTRL+X: cut
    keyMap[ImGuiKey_Y] = SDL_SCANCODE_Y;         // for text edit CTRL+Y: redo
    keyMap[ImGuiKey_Z] = SDL_SCANCODE_Z;         // for text edit CTRL+Z: undo
}
    
void InputLogic::handleImguiInput(const SDL_Event& event)
{
    ImGuiIO& io = ImGui::GetIO();

    if(event.type == SDL_MOUSEBUTTONDOWN)
    {
        auto button = event.button.button;
        if(button == SDL_BUTTON_LEFT)
            io.MouseDown[0] = true;
        else if(button == SDL_BUTTON_RIGHT)
            io.MouseDown[1] = true;
        else if(button == SDL_BUTTON_MIDDLE)
            io.MouseDown[2] = true;
    }
    else if(event.type == SDL_MOUSEBUTTONUP)
    {
        auto button = event.button.button;
    
        if(button == SDL_BUTTON_LEFT)
            io.MouseDown[0] = false;
        else if(button == SDL_BUTTON_RIGHT)
            io.MouseDown[1] = false;
        else if(button == SDL_BUTTON_MIDDLE)
            io.MouseDown[2] = false;
    }
    else if(event.type == SDL_MOUSEWHEEL)
    {
        io.MouseWheel = static_cast<float>(event.wheel.y);
    }
    else if(event.type == SDL_MOUSEMOTION)
    {
        io.MousePos = glm::vec2(event.motion.x, event.motion.y);
    }
    else if(event.type == SDL_KEYDOWN)
    {
        io.KeysDown[event.key.keysym.scancode] = true;
        io.KeyCtrl = event.key.keysym.mod & KMOD_CTRL;
        io.KeyShift = event.key.keysym.mod & KMOD_SHIFT;
        io.KeyAlt = event.key.keysym.mod & KMOD_ALT;
    }
    else if(event.type == SDL_KEYUP)
    {
        io.KeysDown[event.key.keysym.scancode] = false;
        io.KeyCtrl = event.key.keysym.mod & KMOD_CTRL;
        io.KeyShift = event.key.keysym.mod & KMOD_SHIFT;
        io.KeyAlt = event.key.keysym.mod & KMOD_ALT;
    }
    else if(event.type == SDL_TEXTINPUT)
    {
        //if(event.text.text > 0 && event.text.text < 0x10000) not sure why this would be needed or how it would be applied. it was done in elias daler's binding for SFML
        io.AddInputCharactersUTF8(event.text.text);
    }
}
