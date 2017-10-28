#include "game.hpp"
#include <algorithm>

#include <dpx/accesspattern.hpp>
#include <dpx/count.hpp>
#include <dpx/foreach.hpp>
#include <dpx/join.hpp>
#include <dpx/randomget.hpp>
#include <imgui/imgui.h>
#include <input/inputgroup.hpp>
#include <spr/data/entitycollider.hpp>
#include <spr/data/hitbox.hpp>
#include <spr/data/obbcollider.hpp>
#include <spr/data/rotation.hpp>
#include <spr/data/tables.hpp>
#include <spr/debug/debug.hpp>
#include <spr/debug/debugactions.hpp>
#include <spr/debug/debugmenu.hpp>
#include <spr/debugguidata.hpp>
#include <spr/entity/spawnentity.hpp>
#include <spr/entitystates/stateutil.hpp>
#include <spr/gl/texture.hpp>
#include <spr/gl/viewport.hpp>
#include <spr/input/bindingutil.hpp>
#include <spr/input/inputgroup.hpp>
#include <spr/physics/collisiontype.hpp>
#include <spr/profiler/profileblock.hpp>
#include <spr/profiler/profilergui.hpp>
#include <spr/random/random.hpp>
#include <spr/resources/animation.hpp>
#include <spr/resources/audiosample.hpp>
#include <spr/resources/texture.hpp>
#include <spr/showdatatables.hpp>

#include <background/background.hpp>
#include <blood/blood.hpp>
#include <child/child.hpp>
#include <constants/allconstants.hpp>
#include <data/datatables.hpp>
#include <data/angularphysics.hpp>
#include <data/autowalk.hpp>
#include <data/health.hpp>
#include <data/leftsidecleanup.hpp>
#include <debugguidata.hpp>
#include <entity/entityutil.hpp>
#include <entitystates/entitystates.hpp>
#include <showdatatables.hpp>
#include <tablecapacity.hpp>

const spr::GlContextSettings::Type contextType = spr::GlContextSettings::Type::ES;

Game::Game() :
    mWindow(cInitialScreenSize, "Game", {0, 0, 0, 2, 0, contextType}),
    mFrameLogic(mData.frameData, mData.spr),
    mInputLogic(mData.inputData),
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
    io.DeltaTime = 1.0f/60.0f;
    unsigned char* pixels;
    int width, height;
    io.Fonts->GetTexDataAsRGBA32(&pixels, &width, &height);

    mImguiFontTexture = spr::gl::createTexture(glm::ivec2(width, height), pixels, mData.spr);

    io.Fonts->TexID = reinterpret_cast<void*>(get(mImguiFontTexture, *mData.spr.tGlTexture).glId);

    mInputLogic.mapImguiKeys(io.KeyMap);

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
    loadAndAddTexture("blood1"_hash, "assets/blood1.png", mData.spr); 
    loadAndAddTexture("blood2a"_hash, "assets/blood2a.png", mData.spr); 
    loadAndAddTexture("blood2b"_hash, "assets/blood2b.png", mData.spr); 
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
    setupBackground(mData);
    spr::EntityProperties santa = spr::createSpriteProperties({-270.0f, 100.0f, 0.0f}, {}, {}, {48.0f, 48.0f}, *spr::findTexture("santa"_hash, mData.spr), mData.mainShader, mData.mainViewport, mData.worldCamera);

    mData.santaId = addEntity(santa, mData);
    spr::EntityProperties armAnchor = spr::createSceneProperties({-3.0f, 0.0f, 0.0f}, {}, mData.santaId);
    armAnchor["angular_physics"_hash] = AngularPhysics{0.0f, 0.0f, 0.262f};
    mData.armAnchorId = addEntity(armAnchor, mData);

    spr::EntityProperties arm = spr::createSpriteProperties({4.0f, 15.0f, 0.0f}, {}, mData.armAnchorId, {23.0f, 42.0f}, *spr::findTexture("arm"_hash, mData.spr), mData.mainShader, mData.mainViewport, mData.worldCamera);
    mData.armId = addEntity(arm, mData);

    spr::EntityProperties armCollider = spr::createSceneProperties({2.0f, 11.0f, 0.0f}, {}, mData.armId);
    std::vector<spr::CollisionExecutor> executors = {
    {
        "punch",
        [&](const spr::CollisionContext& context)
        {
            if(mData.inputData.ongoingActions.count(PlayerAction::LoadPunch))
            {
                // ignore fist if currently loading punch
            }
            else
            {
                const dpx::TableId fist = context.entityId;
                const dpx::TableId child = context.collidedWithId;
                AutoWalk& autoWalk = dpx::get(child, *mData.game.tAutoWalk);
                int32_t& health = dpx::get(child, *mData.game.tHealth).amount;
                spr::Physics& physics = dpx::get(child, *mData.spr.tPhysics);
                float punchVelocity = std::fabs(dpx::get(mData.armAnchorId, *mData.game.tAngularPhysics).velocity);
                glm::vec2 punchDirection = glm::vec2(1.5f, -3.0f);
                physics.velocity = punchDirection * punchVelocity;
                --health;
                autoWalk.on = false;

                const glm::vec3 position = dpx::get(child, *mData.spr.tPosition).coordinate;
                const float yPos = autoWalk.walkLineY;
                const float speed = 3.0f;
                const int32_t amount = 20;
                spawnBloodSplash(position, yPos, speed, amount, mData);
            }
        }
    }};
    armCollider["entity_collider"_hash] = spr::EntityCollider{spr::EntityCollider::ObbCollider, spr::CollisionType::Trigger, executors};
    armCollider["obb_collider"_hash] = spr::ObbCollider{glm::vec2(19.0f, 19.0f)};
    armCollider["hitbox"_hash] = spr::Hitbox{{glm::vec2(-9.5f, -9.5f), glm::vec2(9.5f, 9.5f)}};
    mData.armColliderId = addEntity(armCollider, mData);
}

void Game::setup(const std::vector<std::string>& args)
{
    if(args.size() > 1 && args[1] == "p")
        mData.paused = true;

    spr::registerInputGroup(InputGroup::Debug, true, mData.inputData);
    spr::registerInputGroup(InputGroup::Global, true, mData.inputData);
    spr::registerInputGroup(InputGroup::Gameplay, true, mData.inputData);

    spr::addBinding(InputGroup::Gameplay, {}, spr::KeyCode::W, PlayerAction::Up, nullptr, mData.inputData);
    spr::addBinding(InputGroup::Gameplay, {}, spr::KeyCode::Up, PlayerAction::Up, nullptr, mData.inputData);
    spr::addBinding(InputGroup::Gameplay, {}, spr::KeyCode::S, PlayerAction::Down, nullptr, mData.inputData);
    spr::addBinding(InputGroup::Gameplay, {}, spr::KeyCode::Down, PlayerAction::Down, nullptr, mData.inputData);
    spr::addBinding(InputGroup::Gameplay, {}, spr::KeyCode::A, PlayerAction::Left, nullptr, mData.inputData);
    spr::addBinding(InputGroup::Gameplay, {}, spr::KeyCode::Left, PlayerAction::Left, nullptr, mData.inputData);
    spr::addBinding(InputGroup::Gameplay, {}, spr::KeyCode::D, PlayerAction::Right, nullptr, mData.inputData);
    spr::addBinding(InputGroup::Gameplay, {}, spr::KeyCode::Right, PlayerAction::Right, nullptr, mData.inputData);
    spr::addBinding(InputGroup::Gameplay, {}, spr::KeyCode::Space, PlayerAction::LoadPunch, nullptr, mData.inputData);

    spr::addBinding(InputGroup::Debug, {}, spr::KeyCode::Comma, spr::DebugAction::ToggleTables, &mData.showTables, mData.inputData);
    spr::addBinding(InputGroup::Debug, {}, spr::KeyCode::Period, spr::DebugAction::ToggleProfiler, &mData.showProfiler, mData.inputData);
    spr::addBinding(InputGroup::Debug, {}, spr::KeyCode::Slash, spr::DebugAction::ToggleDebugMenu, &mData.showDebugMenu, mData.inputData);
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

        mInputLogic.readInput();
        handleSystemInput();

        bool advanceFrame = !mData.paused || mData.advancePaused;
        if(advanceFrame)
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
                    // this is basically only the arm anchor lol
                    const float acc = angPhysics.acceleration;
                    const float maxVel = angPhysics.maximumVelocity;
                    float& vel = angPhysics.velocity;
                    float& rot = rotation.angle;
                    vel += acc;
                    //vel = std::min(vel, maxVel);
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

            if(spr::randomChance(0.01f, mData.randomEngine)) 
            {
                float ySpawnPos = spr::randomFloatRange(mData.bounds.top, mData.bounds.bottom, mData.randomEngine);
                //glm::vec3 childSpawnPosition = {0.0f, ySpawnPos, 0.0f};
                glm::vec3 childSpawnPosition = {425.0f, ySpawnPos, 0.0f};
                int32_t health = 3;
                ChildType type = ChildType::Girl;
                spawnChild(childSpawnPosition, -1.0f, health, type, mData);
                //dpx::TableId newChildId = spawnChild(childSpawnPosition, -1.0f, health, type);
            }
            dpx::join([&](int32_t id, AutoWalk& autoWalk, spr::Position& position, spr::Physics& physics)
            { // for every child every frame
                glm::vec3& pos = position.coordinate;
                if(autoWalk.on) 
                { // autowalking
                    const float vel = autoWalk.velocity;
                    pos.x += vel;
                    physics.velocity = {0.0f, 0.0f};
                    physics.acceleration = {0.0f, 0.0f};
                }
                else
                { // flying away
                    if(pos.y >= autoWalk.walkLineY)
                    { // check they don't fall below walking line
                        pos.y = autoWalk.walkLineY;
                        autoWalk.on = true;
                    }
                    else 
                    {
                        physics.acceleration.y = 0.1f;
                    }
                }
            }, *mData.game.tAutoWalk, *mData.spr.tPosition, *mData.spr.tPhysics);

            dpx::join([&](int32_t id, SplashLanding& splashLanding, spr::Position& position, spr::Physics& physics)
            { // for every blood particle every frame
                glm::vec3& pos = position.coordinate;
                if(pos.y >= splashLanding.landingYCoordinate)
                { // check they don't fall below splashing line
                    pos.y = splashLanding.landingYCoordinate;
                    physics.acceleration = {0.0f, 0.0f};
                    physics.velocity = {0.0f, 0.0f};
                }
            }, *mData.game.tSplashLanding, *mData.spr.tPosition, *mData.spr.tPhysics);

            mEntityLogic.update();

            // making background move
            // spawning more background if necessary

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

void Game::handleSystemInput()
{
    if(mData.inputData.systemInput.quit)
    {
        quit();
    }
    
    if(mData.inputData.systemInput.resized)
    {
        glm::ivec2 size = *mData.inputData.systemInput.resized;
        mData.screenSize = size;

        mRenderLogic.resizeWindow(mData.screenSize);
    }
}

