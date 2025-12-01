/****************************************************************
 * Project Name:  Stardew_Valley
 * File Name:     MapAdapter.cpp
 * File Function: 地图适配器实现
 * Author:        设计模式重构
 * Update Date:   2025/12/01
 * License:       MIT License
 ****************************************************************/

#include "Maps/Adapter/MapAdapter.h"
#include "proj.win32/Constant.h"
#include "Maps/FarmMap.h"
#include "Maps/TownMap.h"
#include "Maps/MineMap.h"
#include "Maps/IndoorMap.h"



GameMap* FarmMapAdapter::createAndAttachMap(const std::string& mapFile,
                                            Node* treeLayer,
                                            Node* mapLayer) {
    if (!_factory) return nullptr;

    // 农场地图需要 TreeLayer，因此这里不使用工厂中传入的 nullptr，
    // 而是直接调用 FarmMap::create，工厂主要负责隐藏类型。
    FarmMap* farmMap = FarmMap::create(mapFile, treeLayer, Vec2(FARM_CREAT_X, FARM_CREAT_Y));
    if (!farmMap) {
        return nullptr;
    }

    if (mapLayer) {
        mapLayer->addChild(farmMap, MAP_LAYER_GRADE);
    }
    return farmMap;
}

Vec2 FarmMapAdapter::getTeleportPosition(GameMap* map) {
    // 目前农场地图没有特殊传送点，直接返回 0,0 或地图中心可按需求调整
    return Vec2::ZERO;
}

GameMap* TownMapAdapter::createAndAttachMap(const std::string& mapFile,
                                            Node* /*treeLayer*/,
                                            Node* mapLayer) {
    if (!_factory) return nullptr;
    GameMap* townMap = _factory->createMap(mapFile, Vec2(TOWN_CREAT_X, TOWN_CREAT_Y));
    if (!townMap) {
        return nullptr;
    }
    if (mapLayer) {
        mapLayer->addChild(townMap, MAP_LAYER_GRADE);
    }
    return townMap;
}

Vec2 TownMapAdapter::getTeleportPosition(GameMap* map) {
    if (!map) return Vec2::ZERO;
    return map->tileToAbsolute(Vec2(TOWN_TELE_X, TOWN_TELE_Y));
}

GameMap* MineMapAdapter::createAndAttachMap(const std::string& mapFile,
                                            Node* /*treeLayer*/,
                                            Node* mapLayer) {
    if (!_factory) return nullptr;
    GameMap* mineMap = _factory->createMap(mapFile, Vec2(MINE_CREAT_X, MINE_CREAT_Y));
    if (!mineMap) {
        return nullptr;
    }
    if (mapLayer) {
        mapLayer->addChild(mineMap, MAP_LAYER_GRADE);
    }
    return mineMap;
}

Vec2 MineMapAdapter::getTeleportPosition(GameMap* map) {
    if (!map) return Vec2::ZERO;
    return map->tileToAbsolute(Vec2(MINE_TELE_X, MINE_TELE_Y));
}

GameMap* IndoorMapAdapter::createAndAttachMap(const std::string& mapFile,
                                              Node* /*treeLayer*/,
                                              Node* mapLayer) {
    if (!_factory) return nullptr;
    GameMap* houseMap = _factory->createMap(mapFile, Vec2(FARM_HOUSE_CREAT_X, FARM_HOUSE_CREAT_Y));
    if (!houseMap) {
        return nullptr;
    }
    if (mapLayer) {
        mapLayer->addChild(houseMap, MAP_LAYER_GRADE);
    }
    return houseMap;
}

Vec2 IndoorMapAdapter::getTeleportPosition(GameMap* map) {
    if (!map) return Vec2::ZERO;
    return map->tileToAbsolute(Vec2(FARM_HOUSE_TELE_X, FARM_HOUSE_TELE_Y));
}


