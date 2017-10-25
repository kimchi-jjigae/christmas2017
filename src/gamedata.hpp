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
#include <startupconstants.hpp>
#include <input/input.hpp>
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
    
    //logic data
    spr::FrameLogic::Data frameData;

    //input
    SystemInput systemInput;
    th::Optional<MouseClick> mouseClick;
    th::Optional<MouseRelease> mouseRelease;
    th::Optional<int32_t> mouseWheel;
    glm::ivec2 mousePosition;
    std::unordered_set<PlayerAction> startedPlayerActions;
    std::unordered_set<PlayerAction> ongoingPlayerActions;
    std::unordered_set<PlayerAction> stoppedPlayerActions;

    //rendering
    dpx::TableId mainShader = dpx::Null;
    dpx::TableId mainViewport = dpx::Null;
    dpx::TableId worldCamera = dpx::Null;
    dpx::TableId guiCamera = dpx::Null;
    
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

    float scrollSpeed = 4.0f;
};
