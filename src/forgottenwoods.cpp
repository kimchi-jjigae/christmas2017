#include "forgottenwoods.hpp"
#include <fea/ui/sdl2windowbackend.hpp>
#include <fea/ui/sdl2inputbackend.hpp>
#include <debugguidata.hpp>
#include "debuggui.hpp"
#include "debug.hpp"
#include <showdatatables.hpp>
#include <imgui.h>
#include "resources/textureutil.hpp"
#include "resources/animationutil.hpp"
#include "renderingutil.hpp"
#include <unordered_set>
#include "land/chunkutil.hpp"
#include "tileutil.hpp"
#include "entity/entityutil.hpp"
#include "entitystates/states/entitystates.hpp"
#include "rendering/renderpasses/renderpasses.hpp"
#include "entitystates/stateutil.hpp"
#include "spawning/spawning.hpp"
#include <tablecapacity.hpp>

#ifdef EMSCRIPTEN
const fea::ContextSettings::Type contextType = fea::ContextSettings::Type::ES;
#else
const fea::ContextSettings::Type contextType = fea::ContextSettings::Type::CORE;
#endif

ForgottenWoods::ForgottenWoods() :
    mWindow(new fea::SDL2WindowBackend(), fea::VideoMode(static_cast<uint32_t>(initialScreenSize.x), static_cast<uint32_t>(initialScreenSize.y)), "ForgottenWoods", fea::Style::Default, fea::ContextSettings(0, 0, 0, 2, 0, contextType)),
    mFeaRenderer(fea::Viewport(initialScreenSize, {0, 0}, fea::Camera(static_cast<glm::vec2>(initialScreenSize / 2)))),
    mFeaInputHandler(new fea::SDL2InputBackend()),
    mInputLogic(mBus, mFeaInputHandler, mData),
    mChunkLogic(mData),
    mCameraLogic(mData),
    mEntityStatesLogic(mData),
    mEntityLogic(mData),
    mCollisionLogic(mData),
    mRenderLogic(mFeaRenderer, mData)
{
    mWindow.setVSyncEnabled(true);
    mWindow.setFramerateLimit(60);

    mFeaInputHandler.setKeyRepeatEnabled(false);

    subscribe(mBus, *this, false);

    //imgui
    ImGuiIO& io = ImGui::GetIO();
    io.DisplaySize.x = mData.screenSize.x;
    io.DisplaySize.y = mData.screenSize.y;
    io.IniFilename = "data/imgui.ini";
    io.MousePos = {0, 0};
    unsigned char* pixels;
    int width, height;
    io.Fonts->GetTexDataAsRGBA32(&pixels, &width, &height);
    mImguiFontTexture.create({width, height}, pixels);
    io.Fonts->TexID = reinterpret_cast<void*>(mImguiFontTexture.getId());

    mRenderLogic.resize(mData.screenSize);

    startScenario();
}

void ForgottenWoods::handleMessage(const QuitMessage& message)
{
    (void)message;
    quit();
}

void ForgottenWoods::handleMessage(const KeyPressedMessage& message)
{
    //if(message.key == fea::Keyboard::A)
    //{
    //    mData.cameraPosition.x += -80;
    //    mData.currentDirection = Direction::Left;
    //}
    //else if(message.key == fea::Keyboard::D)
    //{
    //    mData.cameraPosition.x += 80;
    //    mData.currentDirection = Direction::Right;
    //}
    //else if(message.key == fea::Keyboard::W)
    //{
    //    mData.cameraPosition.y += -80;
    //    mData.currentDirection = Direction::Up;
    //}
    //else if(message.key == fea::Keyboard::S)
    //{
    //    mData.cameraPosition.y += 80;
    //    mData.currentDirection = Direction::Down;
    //}
    if(message.key == fea::Keyboard::R)
        mData.camera.zoom *= 2.0f;
    else if(message.key == fea::Keyboard::F)
        mData.camera.zoom *= 0.5f;
    else if(message.key == fea::Keyboard::C)
        spreadHappiness();
}

void ForgottenWoods::handleMessage(const ResizeMessage& message)
{
    mData.screenSize = message.size;
    ImGuiIO& io = ImGui::GetIO();
    io.DisplaySize.x = mData.screenSize.x;
    io.DisplaySize.y = mData.screenSize.y;
    mRenderLogic.resize(mData.screenSize);
    //mFeaRenderer.setViewport(fea::Viewport(mData.screenSize, {0, 0}, fea::Camera(static_cast<glm::vec2>(mData.screenSize / 2))));
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
    ensureCapacity(50, mData);

    initializeChunkMasks(mData);
    mData.tilesBackgroundTexture = loadAndAddTexture("tiles_background"_hash, "data/textures/bgtiles.png", mData); 
    mData.tilesCenterTexture = loadAndAddTexture("tiles_center"_hash, "data/textures/centertiles.png", mData); 
    mData.fogTexture = loadAndAddTexture("fog"_hash, "data/textures/fog.png", mData); 
    mData.noiseTexture = loadAndAddTexture("noise"_hash, "data/textures/noise.png", mData); 
    mData.wizardTexture = loadAndAddTexture("wizard"_hash, "data/textures/wizard.png", mData); 
    loadAndAddTexture("energy_ball"_hash, "data/textures/energyball.png", mData); 

    addSpriteAnimation("wizard_idle_down"_hash, SpriteAnimation
    {
        {0, 0},
        {12, 14},
        1,
        1
    }, mData);
    addSpriteAnimation("wizard_idle_up"_hash, SpriteAnimation
    {
        {0, 14},
        {12, 14},
        1,
        1
    }, mData);
    addSpriteAnimation("wizard_idle_left"_hash, SpriteAnimation
    {
        {0, 28},
        {12, 14},
        1,
        1
    }, mData);
    addSpriteAnimation("wizard_idle_right"_hash, SpriteAnimation
    {
        {0, 42},
        {12, 14},
        1,
        1
    }, mData);
    addFourDirectionalAnimationGroup("wizard_idle"_hash, FourDirectionalAnimationGroup
    {
        *findAnimation("wizard_idle_up"_hash, mData),
        *findAnimation("wizard_idle_down"_hash, mData),
        *findAnimation("wizard_idle_left"_hash, mData),
        *findAnimation("wizard_idle_right"_hash, mData),
    }, mData);

    addSpriteAnimation("wizard_walk_down"_hash, SpriteAnimation
    {
        {0, 0},
        {12, 14},
        2,
        10
    }, mData);
    addSpriteAnimation("wizard_walk_up"_hash, SpriteAnimation
    {
        {0, 14},
        {12, 14},
        2,
        10
    }, mData);
    addSpriteAnimation("wizard_walk_left"_hash, SpriteAnimation
    {
        {0, 28},
        {12, 14},
        2,
        10
    }, mData);
    addSpriteAnimation("wizard_walk_right"_hash, SpriteAnimation
    {
        {0, 42},
        {12, 14},
        2,
        10
    }, mData);
    addFourDirectionalAnimationGroup("wizard_walk"_hash, FourDirectionalAnimationGroup
    {
        *findAnimation("wizard_walk_up"_hash, mData),
        *findAnimation("wizard_walk_down"_hash, mData),
        *findAnimation("wizard_walk_left"_hash, mData),
        *findAnimation("wizard_walk_right"_hash, mData),
    }, mData);

    addSpriteAnimation("energy_ball"_hash, SpriteAnimation
    {
        {0, 0},
        {8, 8},
        4,
        5
    }, mData);

    registerRenderPasses(mData);
    registerEntityStates(mData);

    int32_t player = spawnPlayer(mData);
}

void ForgottenWoods::loop()
{
    ensureCapacity(50, mData);
    TablesCapacity capacitiesBefore = tablesCapacity(mData);

    //grab input
    mInputLogic.update();

    mCameraLogic.update();

    mChunkLogic.update();
    mEntityStatesLogic.update();
    mEntityLogic.update();

    mCollisionLogic.update();

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

    TablesCapacity capacitiesAfter = tablesCapacity(mData);

    TH_ASSERT(capacitiesBefore == capacitiesAfter, "Spawning crossed capacity boundary in the middle of frame");
}

void ForgottenWoods::temp()
{
}

void ForgottenWoods::spreadHappiness()
{
    auto tileCoord = worldToTile(mData.camera.position);


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
