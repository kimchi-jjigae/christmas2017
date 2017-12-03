#pragma once

#include <cstdint>
#include <map>
#include <random>
#include <unordered_set>

#include <dpx/tables.hpp>
#include <dpx/tableid.hpp>
#include <spr/data/tables.hpp>
#include <spr/physics/quadtree.hpp>
#include <spr/frame/framelogic.hpp>

#include <constants/constants.hpp>
#include <data/datatables.hpp>
#include <player/playeraction.hpp>
#include <rendering/renderlogic.hpp>
#include <startupconstants.hpp>
#include <spr/input/inputlogic.hpp>
#include <spr/profiler/profiler.hpp>

struct GameData
{
    GameData();
    ~GameData();
    //tables
    spr::Tables spr;
    GameTables game;

    //gameplay constants
    std::unique_ptr<constants::Constants> c = constants::makeConstants();
    
    //system
    glm::ivec2 screenSize = cInitialScreenSize;
    bool paused = false;
    int32_t advancePaused = 0;
    bool showDebugMenu = false;
    bool showTables = false;
    bool showProfiler = false;

    //logicdata
    spr::InputLogic::Data inputData;
    spr::FrameLogic::Data frameData;
    RenderLogic::Data renderData;
    
    //entities
    dpx::IdSet entitiesToRemove;
    spr::QuadTree spatialEntityStorage;
    dpx::TableId santaId;
    dpx::TableId armAnchorId;
    dpx::TableId armId;
    dpx::TableId armColliderId;
    
    //random engine
    std::mt19937 randomEngine;

    // profile
    spr::Profiler profiler;

    // misc
    // assuming 0.0f, 0.0f is the middle of the background
    struct Bounds {float top; float bottom; float left; float right;};
    Bounds bounds =
    {
        40.0f, 176.0f, -276.0f, 276.0f
    };

    float scrollSpeed = -0.5f;
};
