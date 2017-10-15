#include "game.hpp"
#include <algorithm>
#include <dpx/accesspattern.hpp>
#include <dpx/randomget.hpp>
#include <dpx/foreach.hpp>
#include <dpx/count.hpp>
#include <dpx/join.hpp>
#include <imgui/imgui.h>
#include <spr/data/entitycollider.hpp>
#include <spr/data/hitbox.hpp>
#include <spr/data/obbcollider.hpp>
#include <spr/data/rotation.hpp>
#include <spr/data/tables.hpp>
#include <spr/debug/debug.hpp>
#include <spr/debug/debugmenu.hpp>
#include <spr/debugguidata.hpp>
#include <spr/entitystates/stateutil.hpp>
#include <spr/entity/spawnentity.hpp>
#include <spr/gl/texture.hpp>
#include <spr/gl/viewport.hpp>
#include <spr/physics/collisiontype.hpp>
#include <spr/profiler/profileblock.hpp>
#include <spr/profiler/profilergui.hpp>
#include <spr/random/random.hpp>
#include <spr/resources/animation.hpp>
#include <spr/resources/texture.hpp>
#include <spr/resources/audiosample.hpp>
#include <spr/showdatatables.hpp>

#include <constants/allconstants.hpp>
#include <data/datatables.hpp>
#include <data/angularphysics.hpp>
#include <data/autowalk.hpp>
#include <debugguidata.hpp>
#include <entity/entityutil.hpp>
#include <entitystates/entitystates.hpp>
#include <showdatatables.hpp>
#include <tablecapacity.hpp>

const spr::GlContextSettings::Type contextType = spr::GlContextSettings::Type::ES;

Game::Game() :
    mWindow(cInitialScreenSize, "Game", {0, 0, 0, 2, 0, contextType}),
    mFrameLogic(mData.frameData, mData.spr),
    mInputLogic(mData),
    mPlayerLogic(mData),
    mEntityStatesLogic(mData.spr),
    mEntityLogic(mData),
    mCollisionLogic(mData.spr),
    mSceneLogic(mData.spr),
    mPhysicsLogic(mData.frameData, mData.spr),
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

    //setup logic settings
    mData.frameData.sFrameTimeMode = spr::FrameTimeMode::Fixed;

    startScenario();
}

Game::~Game()
{
    ImGui::Shutdown();
}

void Game::loadResources()
{
    spr::sprEnsureCapacity(1024, mData.spr);
    ensureCapacity(1024, mData.game);

    //textures
    loadAndAddTexture("bg"_hash, "assets/bg.png", mData.spr); 
    loadAndAddTexture("santa"_hash, "assets/santa.png", mData.spr); 
    loadAndAddTexture("arm"_hash, "assets/arm.png", mData.spr); 
    loadAndAddTexture("child"_hash, "assets/girl.png", mData.spr); 
   
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

void Game::startScenario()
{
    //initialise game
    spr::EntityProperties bg = spr::createSpriteProperties({0.0f, 0.0f, 0.0f}, {}, {}, {640.0f, 400.0f}, *spr::findTexture("bg"_hash, mData.spr), mData.mainShader, mData.mainViewport, mData.worldCamera);
    spr::EntityProperties santa = spr::createSpriteProperties({-270.0f, 100.0f, 0.0f}, {}, {}, {48.0f, 48.0f}, *spr::findTexture("santa"_hash, mData.spr), mData.mainShader, mData.mainViewport, mData.worldCamera);

    addEntity(bg, mData);
    mData.santaId = addEntity(santa, mData);
    spr::EntityProperties armAnchor = spr::createSceneProperties({-3.0f, 0.0f, 0.0f}, {}, mData.santaId);
    armAnchor["angular_physics"_hash] = AngularPhysics{0.0f, 0.0f, 0.262f};
    mData.armAnchorId = addEntity(armAnchor, mData);

    spr::EntityProperties arm = spr::createSpriteProperties({4.0f, 15.0f, 0.0f}, {}, mData.armAnchorId, {23.0f, 42.0f}, *spr::findTexture("arm"_hash, mData.spr), mData.mainShader, mData.mainViewport, mData.worldCamera);
    mData.armId = addEntity(arm, mData);

    spr::EntityProperties armCollider = spr::createSceneProperties({2.0f, 11.0f, 0.0f}, {}, mData.armId);
    armCollider["entity_collider"_hash] = spr::EntityCollider{spr::EntityCollider::ObbCollider, spr::CollisionType::Trigger, {}};
    armCollider["obb_collider"_hash] = spr::ObbCollider{glm::vec2(19.0f, 19.0f)};
    armCollider["hitbox"_hash] = spr::Hitbox{glm::vec2(-9.5f, -9.5f), glm::vec2(9.5f, 9.5f)};
    mData.armColliderId = addEntity(armCollider, mData);
    /*
struct EntityCollider
{
    enum Type { _Base, CircleCollider, ObbCollider, };
    Type entityColliderType;
    CollisionType collisionType;
    std::vector<CollisionExecutor> executors;
};
*/
}

void Game::setup(const std::vector<std::string>& args)
{
    if(args.size() > 1 && args[1] == "p")
        mData.paused = true;
}

void Game::loop()
{
    mFrameLogic.newFrame();
    spr::FrameBlock frameBlock(mData.profiler);

    while(mFrameLogic.timeRemains())
    {
        mFrameLogic.advanceDeltaTime();

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
                dpx::join([&](int32_t id, AngularPhysics& angPhysics, spr::Rotation& rotation)
                {
                    const float acc = angPhysics.acceleration;
                    const float maxVel = angPhysics.maximumVelocity;
                    float& vel = angPhysics.velocity;
                    float& rot = rotation.angle;
                    vel += acc;
                    vel = std::min(vel, maxVel);
                    rot -= vel;
                }, *mData.game.tAngularPhysics, *mData.spr.tRotation);
            }
            mEntityLogic.updateSpatialTree();
            {
                spr::ProfileBlock b("collision"_hash, spr::Color::Green, mData.profiler);
                mCollisionLogic.update();
                //mCollisionLogic.setDebugDraw(true);
            }
            //entity logic
            auto entitiesToRemove = mEntityStatesLogic.update();
            for(dpx::TableId toRemove : entitiesToRemove)
            {
                removeEntity(toRemove, mData);
            }

            glm::vec3 childSpawnPosition = {300.0f, 150.0f, 0.0f};
            if(spr::randomChance(0.01f, mData.randomEngine))
            {
                spr::EntityProperties newChild = spr::createSpriteProperties(childSpawnPosition, {}, {}, {48.0f, 48.0f}, *spr::findTexture("child"_hash, mData.spr), mData.mainShader, mData.mainViewport, mData.worldCamera);
                newChild["auto_walk"_hash] = AutoWalk{-1.0f};
                addEntity(newChild, mData);
            }
            dpx::join([&](int32_t id, AutoWalk& autoWalk, spr::Position& position)
            {
                const float vel = autoWalk.velocity;
                glm::vec3& pos = position.coordinate;
                pos.x += vel;
            }, *mData.game.tAutoWalk, *mData.spr.tPosition);

            mEntityLogic.update();

            if(mData.advancePaused > 0)
                --mData.advancePaused;

            {
                spr::ProfileBlock b("scene_logic"_hash, spr::Color::Brown, mData.profiler);
                mSceneLogic.update();
            }
        }

#ifdef DEBUG_ON
        spr::SprTablesCapacity sprCapacitiesAfter = spr::sprTablesCapacity(mData.spr);
        DataTablesCapacity capacitiesAfter = tablesCapacity(mData.game);
    
        TH_ASSERT(sprCapacitiesBefore == sprCapacitiesAfter, "Spawning crossed capacity boundary in the middle of frame");
        TH_ASSERT(capacitiesBefore == capacitiesAfter, "Spawning crossed capacity boundary in the middle of frame");
#endif
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
        if(mData.showTables)
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

    if(mData.showDebugMenu)
    {
        spr::showDebugMenu(mData.spr);
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
}

void Game::handleInput()
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
