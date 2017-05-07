#pragma once

#include <cstdint>
#include <map>
#include <random>
#include <unordered_set>

#include <dpx/tables.hpp>
#include <dpx/tableid.hpp>
#include <spr/data/tables.hpp>
#include <spr/physics/quadtree.hpp>

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
    bool showProfiler = false;
    
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
    dpx::TableId mainViewport = 0;
    dpx::TableId worldCamera = 0;
    dpx::TableId guiCamera = 0;
    
    //entities
    dpx::IdSet entitiesToRemove;
    spr::QuadTree spatialEntityStorage;
    
    //random engine
    std::mt19937 randomEngine;

    // profile
    spr::Profiler profiler;
};
