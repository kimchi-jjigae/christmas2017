#include "forgottenwoods.hpp"
#include <fea/ui/sdl2windowbackend.hpp>
#include <fea/ui/sdl2inputbackend.hpp>
#include <debugguidata.hpp>
#include "debuggui.hpp"
#include "debug.hpp"
#include <showdatatables.hpp>
#include <imgui.h>
#include "texturemaker.hpp"
#include "renderingutil.hpp"
#include <unordered_set>
#include "land/chunkutil.hpp"
#include "tileutil.hpp"

#ifdef EMSCRIPTEN
const fea::ContextSettings::Type contextType = fea::ContextSettings::Type::ES;
#else
const fea::ContextSettings::Type contextType = fea::ContextSettings::Type::CORE;
#endif

ForgottenWoods::ForgottenWoods() :
    mWindowSize(1366, 768),
    mWindow(new fea::SDL2WindowBackend(), fea::VideoMode(static_cast<uint32_t>(mWindowSize.x), static_cast<uint32_t>(mWindowSize.y)), "ForgottenWoods", fea::Style::Default, fea::ContextSettings(0, 0, 0, 2, 0, contextType)),
    mFeaRenderer(fea::Viewport(mWindowSize, {0, 0}, fea::Camera(static_cast<glm::vec2>(mWindowSize / 2)))),
    mFeaInputHandler(new fea::SDL2InputBackend()),
    mInputHandler(mBus, mFeaInputHandler),
    mChunkPipeline(mData),
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

    mRenderLogic.resize(mWindowSize);

    startScenario();
}

void ForgottenWoods::handleMessage(const QuitMessage& message)
{
    (void)message;
    quit();
}

void ForgottenWoods::handleMessage(const KeyPressedMessage& message)
{
    if(message.key == fea::Keyboard::A)
        mData.cameraPosition.x += -80;
    else if(message.key == fea::Keyboard::D)
        mData.cameraPosition.x += 80;
    else if(message.key == fea::Keyboard::W)
        mData.cameraPosition.y += -80;
    else if(message.key == fea::Keyboard::S)
        mData.cameraPosition.y += 80;
    else if(message.key == fea::Keyboard::R)
        mData.zoom *= 2.0f;
    else if(message.key == fea::Keyboard::F)
        mData.zoom *= 0.5f;
    else if(message.key == fea::Keyboard::C)
        spreadHappiness();
}

void ForgottenWoods::handleMessage(const ResizeMessage& message)
{
    mWindowSize = message.size;
    ImGuiIO& io = ImGui::GetIO();
    io.DisplaySize.x = mWindowSize.x;
    io.DisplaySize.y = mWindowSize.y;
    mRenderLogic.resize(mWindowSize);
    //mFeaRenderer.setViewport(fea::Viewport(mWindowSize, {0, 0}, fea::Camera(static_cast<glm::vec2>(mWindowSize / 2))));
}

void ForgottenWoods::handleMessage(const MouseClickMessage& message)
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

void ForgottenWoods::handleMessage(const MouseReleaseMessage& message)
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

void ForgottenWoods::handleMessage(const MouseMoveMessage& message)
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

void ForgottenWoods::handleMessage(const MouseWheelMessage& message)
{
    ImGuiIO& io = ImGui::GetIO();
    io.MouseWheel = static_cast<float>(message.delta);
}

void ForgottenWoods::startScenario()
{
    initializeChunkMasks(mData);
    mData.cameraPosition = {30000, 30000};
    mData.tilesBackgroundTexture = makeTexture("data/textures/bgtiles.png"); 
    mData.tilesCenterTexture = makeTexture("data/textures/centertiles.png"); 
    mData.fogTexture = makeTexture("data/textures/fog.png"); 
    mData.noiseTexture = makeTexture("data/textures/noise.png"); 
    insert({10, {5.0f, 5.0f}, {"I", "have", "some", "text"}}, mData.tHelloWorld);
    insert({20, {1.0f, 1.0f}, {"Me", "too"}}, mData.tHelloWorld);
}

void ForgottenWoods::loop()
{
    //grab input
    mInputHandler.process();

    temp();

    mChunkPipeline.update();

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

void ForgottenWoods::temp()
{
    glm::ivec2 size = {mWindow.getSize().x, mWindow.getSize().y};

    auto start = mData.cameraPosition - size / 2;
    auto end = mData.cameraPosition + size / 2;

    std::unordered_set<glm::ivec2> points =
    {
        {start.x, start.y},
        {start.x, end.y},
        {end.x, start.y},
        {end.x, end.y},
    };
    
    std::unordered_set<glm::ivec2> chunksThatWereInView;

    for(auto point : points)
    {
        auto chunkCoord = point / TileWidth / ChunkWidth;

        if(mData.worldChunks.count(chunkCoord) == 0 && std::count(mData.chunksToLoad.begin(), mData.chunksToLoad.end(), chunkCoord) == 0)
        {
            mData.chunksToLoad.emplace_back(chunkCoord);
        }

        if(mData.chunksInView.count(chunkCoord) == 0 && std::count(mData.chunksToPutInView.begin(), mData.chunksToPutInView.end(), chunkCoord) == 0)
            mData.chunksToPutInView.emplace_back(chunkCoord);
        chunksThatWereInView.emplace(chunkCoord);
    }

    for(const auto& iter : mData.chunksInView)
    {
        if(chunksThatWereInView.count(iter.first) == 0)
            mData.chunksThatLeftView.emplace_back(iter.first);
    }
}

void ForgottenWoods::spreadHappiness()
{
    auto tileCoord = worldToTile(mData.cameraPosition);


    for(int32_t y = tileCoord.y - 6; y < tileCoord.y + 6; ++y)
    {
        for(int32_t x = tileCoord.x - 6; x < tileCoord.x + 6; ++x)
        {
            float distance = glm::distance(static_cast<glm::vec2>(tileCoord), glm::vec2(x, y));
            int32_t increase = std::max(0.0f, 8.5f - distance + (rand() % 8) / 10.0f) / 2;
            setTileGoodness({x, y}, std::min(99, tileGoodness({x, y}, mData) + increase), mData);
        }
    }
}
