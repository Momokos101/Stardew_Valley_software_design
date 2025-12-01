/****************************************************************
 * Project Name:  Stardew_Valley
 * File Name:     MapFactory.h
 * File Function: 地图抽象工厂接口与具体工厂声明
 * Author:        设计模式重构
 * Update Date:   2024/12/17
 * License:       MIT License
 ****************************************************************/
#ifndef MAP_FACTORY_H
#define MAP_FACTORY_H

#include "cocos2d.h"
#include <string>
#include "Maps/GameMap.h"
#include "Maps/FarmMap.h"
#include "Maps/TownMap.h"
#include "Maps/MineMap.h"
#include "Maps/IndoorMap.h"

USING_NS_CC;

/**
 * 抽象地图工厂：
 *  - 负责创建具体的 GameMap 子类
 *  - 未来可以扩展创建动物 / NPC / 作物等相关对象
 */
class MapFactory {
public:
    virtual ~MapFactory() = default;

    /**
     * 创建并初始化地图对象。
     * @param mapFile 地图资源文件
     * @param position 地图起始位置
     */
    virtual GameMap* createMap(const std::string& mapFile,
                               const Vec2& position) = 0;
};

class FarmMapFactory : public MapFactory {
public:
    GameMap* createMap(const std::string& mapFile,
                       const Vec2& position) override;
};

class TownMapFactory : public MapFactory {
public:
    GameMap* createMap(const std::string& mapFile,
                       const Vec2& position) override;
};

class MineMapFactory : public MapFactory {
public:
    GameMap* createMap(const std::string& mapFile,
                       const Vec2& position) override;
};

class IndoorMapFactory : public MapFactory {
public:
    GameMap* createMap(const std::string& mapFile,
                       const Vec2& position) override;
};

#endif // MAP_FACTORY_H


