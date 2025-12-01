/****************************************************************
 * Project Name:  Stardew_Valley
 * File Name:     DefaultMapImplementation.h
 * File Function: 默认地图实现（适用于当前所有基于 TMXTiledMap 的地图）
 * Author:        设计模式重构
 * Update Date:   2024/12/17
 * License:       MIT License
 ****************************************************************/
#ifndef DEFAULT_MAP_IMPLEMENTATION_H
#define DEFAULT_MAP_IMPLEMENTATION_H

#include "MapImplementation.h"

/**
 * 默认的地图实现类：
 * 其行为与当前 GameMap 中的实现一致，
 * 作为 Bridge 模式下的一个具体 Implementor。
 */
class DefaultMapImplementation : public MapImplementation {
public:
    Vec2 absoluteToTile(TMXTiledMap* tileMap,
                        const Vec2& mapPosition,
                        float mapScale,
                        const Vec2& pixelPoint) override;

    Vec2 tileToAbsolute(TMXTiledMap* tileMap,
                        const Vec2& mapPosition,
                        float mapScale,
                        const Vec2& tileCoord) override;

    Vec2 tileToRelative(TMXTiledMap* tileMap,
                        const Vec2& mapPosition,
                        const Vec2& tileCoord) override;

    int getTileGIDAt(TMXTiledMap* tileMap,
                     const std::string& layerName,
                     const Vec2& tileCoord) const override;

    cocos2d::ValueMap getTilePropertiesForGID(TMXTiledMap* tileMap,
                                              int GID) const override;

    void replaceTileAt(TMXTiledMap* tileMap,
                       const std::string& layerName,
                       const Vec2& tileCoord,
                       int newGID) override;
};

#endif // DEFAULT_MAP_IMPLEMENTATION_H


