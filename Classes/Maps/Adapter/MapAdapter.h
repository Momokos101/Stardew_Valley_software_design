/****************************************************************
 * Project Name:  Stardew_Valley
 * File Name:     MapAdapter.h
 * File Function: 地图适配器接口与具体适配器声明
 * Author:        设计模式重构
 * Update Date:   2024/12/17
 * License:       MIT License
 ****************************************************************/
#ifndef MAP_ADAPTER_H
#define MAP_ADAPTER_H

#include "cocos2d.h"
#include <string>
#include "Maps/GameMap.h"
#include "Maps/Factory/MapFactory.h"

USING_NS_CC;

/**
 * Adapter 模式中的目标接口：
 *  - 为 MapSwitchManager 提供统一的地图创建与传送点获取接口
 */
class MapAdapter {
public:
    virtual ~MapAdapter() = default;

    /**
     * 创建并初始化地图。
     * @param mapFile 地图文件
     * @param treeLayer 农场树木层（仅农场地图需要，其它地图可忽略）
     * @param mapLayer  场景中的地图父节点
     */
    virtual GameMap* createAndAttachMap(const std::string& mapFile,
                                        Node* treeLayer,
                                        Node* mapLayer) = 0;

    /**
     * 获取角色传送落点（世界坐标）。
     */
    virtual Vec2 getTeleportPosition(GameMap* map) = 0;
};

class FarmMapAdapter : public MapAdapter {
public:
    explicit FarmMapAdapter(FarmMapFactory* factory)
        : _factory(factory) {}

    GameMap* createAndAttachMap(const std::string& mapFile,
                                Node* treeLayer,
                                Node* mapLayer) override;

    Vec2 getTeleportPosition(GameMap* map) override;

private:
    FarmMapFactory* _factory;
};

class TownMapAdapter : public MapAdapter {
public:
    explicit TownMapAdapter(TownMapFactory* factory)
        : _factory(factory) {}

    GameMap* createAndAttachMap(const std::string& mapFile,
                                Node* treeLayer,
                                Node* mapLayer) override;

    Vec2 getTeleportPosition(GameMap* map) override;

private:
    TownMapFactory* _factory;
};

class MineMapAdapter : public MapAdapter {
public:
    explicit MineMapAdapter(MineMapFactory* factory)
        : _factory(factory) {}

    GameMap* createAndAttachMap(const std::string& mapFile,
                                Node* treeLayer,
                                Node* mapLayer) override;

    Vec2 getTeleportPosition(GameMap* map) override;

private:
    MineMapFactory* _factory;
};

class IndoorMapAdapter : public MapAdapter {
public:
    explicit IndoorMapAdapter(IndoorMapFactory* factory)
        : _factory(factory) {}

    GameMap* createAndAttachMap(const std::string& mapFile,
                                Node* treeLayer,
                                Node* mapLayer) override;

    Vec2 getTeleportPosition(GameMap* map) override;

private:
    IndoorMapFactory* _factory;
};

#endif // MAP_ADAPTER_H


