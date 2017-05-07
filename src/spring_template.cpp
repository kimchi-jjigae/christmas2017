#include "spring_template.hpp"
#include <dpx/accesspattern.hpp>
#include <dpx/randomget.hpp>
#include <dpx/foreach.hpp>
#include <dpx/count.hpp>
#include <imgui.h>
#include <spr/data/tables.hpp>
#include <spr/debugguidata.hpp>
#include <spr/entitystates/stateutil.hpp>
#include <spr/debug/debug.hpp>
#include <spr/showdatatables.hpp>
#include <spr/profiler/profilergui.hpp>
#include <spr/gl/texture.hpp>
#include <spr/gl/viewport.hpp>

#include <constants/allconstants.hpp>
#include <data/datatables.hpp>
#include <debugguidata.hpp>
#include <entity/entityutil.hpp>
#include <entitystates/entitystates.hpp>
#include <spr/resources/animation.hpp>
#include <spr/resources/texture.hpp>
#include <spr/resources/audiosample.hpp>
#include <showdatatables.hpp>
#include <tablecapacity.hpp>
#include <spr/profiler/profileblock.hpp>

const spr::GlContextSettings::Type contextType = spr::GlContextSettings::Type::ES;

SpringTemplate::SpringTemplate() :
    mWindow(cInitialScreenSize, "SpringTemplate", {0, 0, 0, 2, 0, contextType}),
    mInputLogic(mData),
    mPlayerLogic(mData),
    mEntityStatesLogic(mData.spr),
    mEntityLogic(mData),
    mCollisionLogic(mData.spr),
    mSceneLogic(mData.spr),
    mPhysicsLogic(mData.spr),
    mRenderLogic(mData),
    mAudioLogic(mData.spr)
{
    mData.randomEngine.seed(std::random_device()());

    mWindow.setVSync(true);

    //imgui
    ImGuiIO& io = ImGui::GetIO();
    io.DisplaySize.x = static_cast<float>(mData.screenSize.x);
    io.DisplaySize.y = static_cast<float>(mData.screenSize.y);
    io.IniFilename = "data/imgui.ini";
    io.MousePos = {0, 0};
    unsigned char* pixels;
    int width, height;
    io.Fonts->GetTexDataAsRGBA32(&pixels, &width, &height);

    mImguiFontTexture = spr::gl::createTexture(glm::ivec2(width, height), pixels, mData.spr);

    io.Fonts->TexID = reinterpret_cast<void*>(get(mImguiFontTexture, *mData.spr.tGlTexture).glId);

    loadResources();

    mRenderLogic.resizeWindow(mData.screenSize);

    float spatialStorageSize = mData.c->world->spatialStorageSize;
    mData.spatialEntityStorage = spr::QuadTree({mData.c->world->spatialStorageSize, mData.c->world->spatialStorageSize});
    mCollisionLogic.setQuadTree(mData.spatialEntityStorage, {spatialStorageSize / 2.0f, spatialStorageSize / 2.0f});
}

void SpringTemplate::loadResources()
{
    spr::sprEnsureCapacity(1024, mData.spr);
    ensureCapacity(1024, mData.game);

    //textures
    //loadAndAddTexture("bullet"_hash,     "data/textures/weapon/bullet.png",    mData.spr); 
   
    //animations
    //addSpriteAnimation("explosion"_hash, spr::SpriteAnimation
    //{
    //    {0, 0},
    //    {48, 48},
    //    3,
    //    8
    //}, mData.spr);

    //audio
    //loadAndAddAudioSample("shoot_bullet"_hash, "data/audio/bulletshoot.ogg", mData.spr);

    registerEntityStates(mData);
}

void SpringTemplate::startScenario()
{
    //initialise game
}

void SpringTemplate::setup(const std::vector<std::string>& args)
{
    if(args.size() > 1 && args[1] == "p")
        mData.paused = true;
}

void SpringTemplate::loop()
{
    spr::FrameBlock frameBlock(mData.profiler);

    spr::sprEnsureCapacity(1024, mData.spr);
    ensureCapacity(1024, mData.game);

#ifdef DEBUG_ON
    spr::SprTablesCapacity sprCapacitiesBefore = spr::sprTablesCapacity(mData.spr);
    DataTablesCapacity capacitiesBefore = tablesCapacity(mData.game);
#endif

    mInputLogic.update();
    handleInput();

    if(!mData.paused || mData.advancePaused)
    {
        {
            spr::ProfileBlock b("player_logic"_hash, spr::Color::Yellow, mData.profiler);
            mPlayerLogic.update();
        }
        {
            spr::ProfileBlock b("physics"_hash, spr::Color::Red, mData.profiler);
            mPhysicsLogic.update();
        }
        mEntityLogic.updateSpatialTree();
        {
            spr::ProfileBlock b("collision"_hash, spr::Color::Green, mData.profiler);
            mCollisionLogic.update();
        }
        {
            spr::ProfileBlock b("scene_logic"_hash, spr::Color::Brown, mData.profiler);
            mSceneLogic.update();
        }

        //entity logic
        auto entitiesToRemove = mEntityStatesLogic.update();
        for(dpx::TableId toRemove : entitiesToRemove)
        {
            removeEntity(toRemove, mData);
        }

        mEntityLogic.update();

        if(mData.advancePaused > 0)
            --mData.advancePaused;
    }

    //imgui
    ImGuiIO& io = ImGui::GetIO();
    mGuiBlocksMouse = io.WantCaptureMouse;
    io.DeltaTime = 1.0f/60.0f;

    {
        spr::ProfileBlock b("clear_screen"_hash, spr::Color::Gray, mData.profiler);
        mRenderLogic.frameStart(mData.c->world->voidColor);
    }

    {
        spr::ProfileBlock b("datatables"_hash, spr::Color::Pink, mData.profiler);
        if(mData.showDebugMenu)
        {
            spr::showDataTables("Spring tables", mClickedEntity, mData.spr);
            showDataTables("Game tables", mClickedEntity, mData.game, mData.spr);
        }
    }

    if(mData.showProfiler)
    {
        spr::ProfileBlock b("profiler_gui"_hash, spr::Color::Yellow, mData.profiler);
        showProfilerGui(mData.profiler);
    }

    {
        spr::ProfileBlock b("rendering"_hash, spr::Color::Blue, mData.profiler);
        mRenderLogic.renderFrame();
    }

    {
        spr::ProfileBlock b("swap"_hash, spr::Color::White, mData.profiler);
        mWindow.swapBuffers();
    }

    {
        spr::ProfileBlock b("audio"_hash, spr::Color::Tan, mData.profiler);
        mAudioLogic.update();
    }

#ifdef DEBUG_ON
    spr::SprTablesCapacity sprCapacitiesAfter = spr::sprTablesCapacity(mData.spr);
    DataTablesCapacity capacitiesAfter = tablesCapacity(mData.game);

    TH_ASSERT(sprCapacitiesBefore == sprCapacitiesAfter, "Spawning crossed capacity boundary in the middle of frame");
    TH_ASSERT(capacitiesBefore == capacitiesAfter, "Spawning crossed capacity boundary in the middle of frame");
#endif
}

void SpringTemplate::handleInput()
{
    ImGuiIO& io = ImGui::GetIO();

    if(mData.systemInput.quit)
    {
        quit();
    }
    
    if(mData.systemInput.resized)
    {
        glm::ivec2 size = *mData.systemInput.resized;
        mData.screenSize = size;

        io.DisplaySize.x = static_cast<float>(mData.screenSize.x);
        io.DisplaySize.y = static_cast<float>(mData.screenSize.y);

        mRenderLogic.resizeWindow(mData.screenSize);
    }
    
    if(mData.mouseClick)
    {
        auto button = mData.mouseClick->button;
        if(button == MouseButton::Left)
            io.MouseDown[0] = true;
        else if(button == MouseButton::Right)
            io.MouseDown[1] = true;
        else if(button == MouseButton::Middle)
            io.MouseDown[2] = true;
    }
    
    if(mData.mouseRelease)
    {
        auto button = mData.mouseRelease->button;
    
        if(button == MouseButton::Left)
            io.MouseDown[0] = false;
        else if(button == MouseButton::Right)
            io.MouseDown[1] = false;
        else if(button == MouseButton::Middle)
            io.MouseDown[2] = false;
    }
    
    if(mData.mouseWheel)
    {
        io.MouseWheel = static_cast<float>(*mData.mouseWheel);
    }
    
    io.MousePos = static_cast<glm::vec2>(mData.mousePosition);
}
