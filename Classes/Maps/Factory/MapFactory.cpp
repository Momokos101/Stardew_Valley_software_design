/****************************************************************
 * Project Name:  Stardew_Valley
 * File Name:     MapFactory.cpp
 * File Function: 地图抽象工厂具体实现
 * Author:        设计模式重构
 * Update Date:   2024/12/17
 * License:       MIT License
 ****************************************************************/

#include "Maps/Factory/MapFactory.h"

GameMap* FarmMapFactory::createMap(const std::string& mapFile,
                                   const Vec2& position) {
    // FarmMap 目前额外需要 TreeLayer，由调用方负责传入并在 FarmMap::create 中使用
    // 这里仅负责创建 FarmMap 本体，TreeLayer 仍由地图切换管理器处理
    // 为保持现有接口兼容，暂时传入 nullptr，后续可扩展为在工厂中处理 TreeLayer
    return FarmMap::create(mapFile, nullptr, position);
}

GameMap* TownMapFactory::createMap(const std::string& mapFile,
                                   const Vec2& position) {
    return TownMap::create(mapFile, position);
}

GameMap* MineMapFactory::createMap(const std::string& mapFile,
                                   const Vec2& position) {
    return MineMap::create(mapFile, position);
}

GameMap* IndoorMapFactory::createMap(const std::string& mapFile,
                                     const Vec2& position) {
    return IndoorMap::create(mapFile, position);
}


