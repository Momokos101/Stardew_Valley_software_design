/****************************************************************
 * Project Name:  Stardew_Valley
 * File Name:     DefaultMapImplementation.cpp
 * File Function: 默认地图实现（基于 TMXTiledMap 的具体实现）
 * Author:        设计模式重构
 * Update Date:   2024/12/17
 * License:       MIT License
 ****************************************************************/

#include "DefaultMapImplementation.h"

Vec2 DefaultMapImplementation::absoluteToTile(TMXTiledMap* tileMap,
                                              const Vec2& mapPosition,
                                              float mapScale,
                                              const Vec2& pixelPoint) {
    if (!tileMap) {
        return Vec2::ZERO;
    }

    // 获取瓦片大小
    Size tileSize = tileMap->getTileSize();

    float tileX = (pixelPoint.x - mapPosition.x) / (tileSize.width * mapScale);
    float tileY = (pixelPoint.y - mapPosition.y) / (tileSize.height * mapScale);

    // 瓦片地图左上坐标系的y轴是翻转的
    tileY = tileMap->getMapSize().height - tileY;

    return Vec2(floor(tileX), floor(tileY));
}

Vec2 DefaultMapImplementation::tileToAbsolute(TMXTiledMap* tileMap,
                                              const Vec2& mapPosition,
                                              float mapScale,
                                              const Vec2& tileCoord) {
    if (!tileMap) {
        return Vec2::ZERO;
    }

    // 获取瓦片大小
    Size tileSize = tileMap->getTileSize();

    // 计算瓦片左下角的绝对坐标
    float pixelX = tileCoord.x * tileSize.width * mapScale + mapPosition.x;
    float pixelY = (tileMap->getMapSize().height - tileCoord.y - 1) * tileSize.height * mapScale + mapPosition.y;

    // 加上瓦片一半的宽高，得到瓦片的中点坐标
    pixelX += (tileSize.width * mapScale) / 2.0f;
    pixelY += (tileSize.height * mapScale) / 2.0f;

    return Vec2(pixelX, pixelY);
}

Vec2 DefaultMapImplementation::tileToRelative(TMXTiledMap* tileMap,
                                              const Vec2& mapPosition,
                                              const Vec2& tileCoord) {
    if (!tileMap) {
        return Vec2::ZERO;
    }

    // 获取瓦片大小
    Size tileSize = tileMap->getTileSize();

    // 计算瓦片左下角的绝对坐标
    float pixelX = tileCoord.x * tileSize.width + mapPosition.x;
    float pixelY = (tileMap->getMapSize().height - tileCoord.y - 1) * tileSize.height + mapPosition.y;

    // 加上瓦片一半的宽高，得到瓦片的中点坐标
    pixelX += (tileSize.width) / 2.0f;
    pixelY += (tileSize.height) / 2.0f;

    return Vec2(pixelX, pixelY);
}

int DefaultMapImplementation::getTileGIDAt(TMXTiledMap* tileMap,
                                           const std::string& layerName,
                                           const Vec2& tileCoord) const {
    if (!tileMap) {
        return 0;
    }

    auto layer = tileMap->getLayer(layerName);
    if (!layer) {
        return 0;
    }

    auto mapSize = tileMap->getMapSize();
    if (tileCoord.x < 0 || tileCoord.y < 0 ||
        tileCoord.x >= mapSize.width || tileCoord.y >= mapSize.height) {
        return 0;
    }

    return layer->getTileGIDAt(tileCoord);
}

cocos2d::ValueMap DefaultMapImplementation::getTilePropertiesForGID(TMXTiledMap* tileMap,
                                                                    int GID) const {
    if (!tileMap || GID == 0) {
        return cocos2d::ValueMap();
    }

    auto tileProperties = tileMap->getPropertiesForGID(GID);
    if (tileProperties.getType() == Value::Type::MAP) {
        return tileProperties.asValueMap();
    }
    return cocos2d::ValueMap();
}

void DefaultMapImplementation::replaceTileAt(TMXTiledMap* tileMap,
                                             const std::string& layerName,
                                             const Vec2& tileCoord,
                                             int newGID) {
    if (!tileMap) {
        return;
    }

    // 获取目标图层
    TMXLayer* layer = tileMap->getLayer(layerName);
    if (!layer) {
        CCLOG("Layer '%s' not found!", layerName.c_str());
        return;
    }

    // 检查瓦片坐标是否有效
    auto mapSize = tileMap->getMapSize(); // 地图尺寸（瓦片数）
    if (tileCoord.x < 0 || tileCoord.y < 0 ||
        tileCoord.x >= mapSize.width || tileCoord.y >= mapSize.height) {
        CCLOG("Tile position (%f, %f) is out of bounds!", tileCoord.x, tileCoord.y);
        return;
    }

    // 设置新瓦片
    layer->setTileGID(newGID, tileCoord);
    CCLOG("Replaced tile at (%f, %f) on layer '%s' with GID=%d",
          tileCoord.x, tileCoord.y, layerName.c_str(), newGID);
}


