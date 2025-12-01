/****************************************************************
 * Project Name:  Stardew_Valley
 * File Name:     MapImplementation.h
 * File Function: 地图实现接口（Bridge 模式的 Implementor）
 * Author:        设计模式重构
 * Update Date:   2024/12/17
 * License:       MIT License
 ****************************************************************/
#ifndef MAP_IMPLEMENTATION_H
#define MAP_IMPLEMENTATION_H

#include "cocos2d.h"
#include "2d/CCTMXTiledMap.h"
#include <string>

USING_NS_CC;

/**
 * Bridge 模式中的实现接口：
 * 负责封装与 TMXTiledMap 相关的具体操作，
 * GameMap 作为抽象层只通过该接口访问地图实现。
 */
class MapImplementation {
public:
    virtual ~MapImplementation() = default;

    virtual Vec2 absoluteToTile(TMXTiledMap* tileMap,
                                const Vec2& mapPosition,
                                float mapScale,
                                const Vec2& pixelPoint) = 0;

    virtual Vec2 tileToAbsolute(TMXTiledMap* tileMap,
                                const Vec2& mapPosition,
                                float mapScale,
                                const Vec2& tileCoord) = 0;

    virtual Vec2 tileToRelative(TMXTiledMap* tileMap,
                                const Vec2& mapPosition,
                                const Vec2& tileCoord) = 0;

    virtual int getTileGIDAt(TMXTiledMap* tileMap,
                             const std::string& layerName,
                             const Vec2& tileCoord) const = 0;

    virtual cocos2d::ValueMap getTilePropertiesForGID(TMXTiledMap* tileMap,
                                                      int GID) const = 0;

    virtual void replaceTileAt(TMXTiledMap* tileMap,
                               const std::string& layerName,
                               const Vec2& tileCoord,
                               int newGID) = 0;
};

#endif // MAP_IMPLEMENTATION_H


