#include "changeme.hpp"
#include <fea/ui/sdl2windowbackend.hpp>
#include <fea/ui/sdl2inputbackend.hpp>
#include <debugguidata.hpp>
#include "debuggui.hpp"
#include "debug.hpp"
#include <showdatatables.hpp>
#include <imgui.h>

#ifdef EMSCRIPTEN
const fea::ContextSettings::Type contextType = fea::ContextSettings::Type::ES;
#else
const fea::ContextSettings::Type contextType = fea::ContextSettings::Type::CORE;
#endif

ChangeMe::ChangeMe() :
    mWindowSize(1366, 768),
    mWindow(new fea::SDL2WindowBackend(), fea::VideoMode(static_cast<uint32_t>(mWindowSize.x), static_cast<uint32_t>(mWindowSize.y)), "ChangeMe", fea::Style::Default, fea::ContextSettings(0, 0, 0, 2, 0, contextType)),
    mFeaRenderer(fea::Viewport(mWindowSize, {0, 0}, fea::Camera(static_cast<glm::vec2>(mWindowSize / 2)))),
    mFeaInputHandler(new fea::SDL2InputBackend()),
    mInputHandler(mBus, mFeaInputHandler),
    mRenderLogic(mFeaRenderer, mData)
{
    mWindow.setVSyncEnabled(true);
    mWindow.setFramerateLimit(60);

    subscribe(mBus, *this, false);

    //imgui
    ImGuiIO& io = ImGui::GetIO();
    io.DisplaySize.x = mWindowSize.x;
    io.DisplaySize.y = mWindowSize.y;
    io.IniFilename = "data/imgui.ini";
    io.MousePos = {0, 0};
    unsigned char* pixels;
    int width, height;
    io.Fonts->GetTexDataAsRGBA32(&pixels, &width, &height);
    mImguiFontTexture.create({width, height}, pixels);
    io.Fonts->TexID = reinterpret_cast<void*>(mImguiFontTexture.getId());

    startScenario();
}

void ChangeMe::handleMessage(const QuitMessage& message)
{
    (void)message;
    quit();
}

void ChangeMe::handleMessage(const KeyPressedMessage& message)
{
}

void ChangeMe::handleMessage(const ResizeMessage& message)
{
    mWindowSize = message.size;
    ImGuiIO& io = ImGui::GetIO();
    io.DisplaySize.x = mWindowSize.x;
    io.DisplaySize.y = mWindowSize.y;
    mFeaRenderer.setViewport(fea::Viewport(mWindowSize, {0, 0}, fea::Camera(static_cast<glm::vec2>(mWindowSize / 2))));
}

void ChangeMe::handleMessage(const MouseClickMessage& message)
{
    if(!mGuiBlocksMouse)
    {
        //mInterfaceLogic.worldMouseClick(message.position, message.position / 32, message.button);
    }

    ImGuiIO& io = ImGui::GetIO();

    if(message.button == fea::Mouse::LEFT)
        io.MouseDown[0] = true;
    else if(message.button == fea::Mouse::RIGHT)
        io.MouseDown[1] = true;
}

void ChangeMe::handleMessage(const MouseReleaseMessage& message)
{
    if(!mGuiBlocksMouse)
    {
        //mInterfaceLogic.worldMouseRelease(message.position, message.position / 32, message.button);
    }

    ImGuiIO& io = ImGui::GetIO();

    if(message.button == fea::Mouse::LEFT)
        io.MouseDown[0] = false;
    else if(message.button == fea::Mouse::RIGHT)
        io.MouseDown[1] = false;
}

void ChangeMe::handleMessage(const MouseMoveMessage& message)
{
    ImGuiIO& io = ImGui::GetIO();
    io.MousePos = (glm::vec2)message.position;

    //auto position = message.position / 32;
    //position.x = std::max(position.x, 0);
    //position.y = std::max(position.y, 0);

    if(!mGuiBlocksMouse)
    {
        //if(message.drag)
        //    mInterfaceLogic.worldMouseDrag(message.position, message.position / 32, fea::Mouse::LEFT);
    }
}

void ChangeMe::handleMessage(const MouseWheelMessage& message)
{
    ImGuiIO& io = ImGui::GetIO();
    io.MouseWheel = static_cast<float>(message.delta);
}

void ChangeMe::startScenario()
{
    insert({10, {5.0f, 5.0f}, {"I", "have", "some", "text"}}, mData.tHelloWorld);
    insert({20, {1.0f, 1.0f}, {"Me", "too"}}, mData.tHelloWorld);
}

void ChangeMe::loop()
{
    //grab input
    mInputHandler.process();

    //imgui
    ImGuiIO& io = ImGui::GetIO();
    mGuiBlocksMouse = io.WantCaptureMouse;
    io.DeltaTime = 1.0f/60.0f;

    mRenderLogic.frameStart();

    ImGui::ShowTestWindow();

    DebugGui::showDataTables(mClickedEntity, mData);
    //DebugGui::showDataTables(mClickedEntity,
    //        mData.tPosition, mData.tPhysics, mData.tCollisionBox, mData.tWalkTarget, mData.tMoveAbility, mData.tMoveIntention, mData.tBloodValues, mData.tChoking,
    //        mData.tAi, mData.uninitializedAis, mData.humanAis,
    //        mData.tIncentive, mData.activeIncentives, mData.tBreatheIncentive, mData.tWorkIncentive,
    //        mData.tAction, mData.leafActions, mData.tTaskAction, mData.tGotoAction, mData.tTotalPanicAction, mData.tFindWorkTaskAction, mData.tConstructWallAction, mData.tConstructDoorAction,
    //        mData.tStructureType, mData.tStructure, mData.uninitializedStructures,
    //        mData.tAirlock, mData.tAirlockActivity,
    //        mData.tDoor, mData.tStructureDoorLock, mData.tZoneLeak, mData.openDoors, mData.lockedDoors,
    //        mData.tTask, mData.tRoomTask, mData.tWallTask, mData.tDoorTask, mData.unassignedTasks, mData.tAssignedTask,
    //        mData.tItem, mData.tWearable, mData.tItemContainer, mData.tItemStoring, mData.tAirTank,
    //        mData.tPath,
    //        mData.builders, mData.freeWorkers, mData.tBusyWorker, mData.deadWorkers, mData.tActorSprite);

    if(mClickedEntity)
        dbg::set<int32_t>("selected_actor", *mClickedEntity);

    mRenderLogic.update();
    //mInterfaceLogic.update();

    mRenderLogic.frameEnd();

    mWindow.swapBuffers();
}

void ChangeMe::temp()
{
}
