/****************************************************************
 * Project Name:  Stardew_Valley
 * File Name:     FarmMap.cpp
 * File Function: 地图基类Map类的实现
 * Author:        金恒宇
 * Update Date:   2024/12/11
 * License:       MIT License
 ****************************************************************/

#include "GameMap.h"
#include "Maps/Bridge/DefaultMapImplementation.h"

USING_NS_CC;

GameMap::GameMap(const Vec2& mapPosition)
    : _tile_map(nullptr),
      _map_position(mapPosition) {
_implementation = std::make_unique<DefaultMapImplementation>();
}

GameMap::~GameMap() {}

// 创建地图
GameMap* GameMap::create(const std::string& mapFile, const Vec2& mapPosition)
{
    GameMap* ret = new GameMap(mapPosition);
    if (ret && ret->init(mapFile, mapPosition)) {
        ret->autorelease();
        return ret;
    }
    else {
        delete ret;
        return nullptr;
    }
}

// 初始化地图
bool GameMap::init(const std::string& mapFile, const Vec2& mapPosition)
{
    // 调用基类初始化方法
    if (!Node::init()) {
        return false;
    }
    _mapName = mapFile;
    // 加载地图
    _tile_map = TMXTiledMap::create(mapFile);
    if (!_tile_map) {
        CCLOG("Failed to load map");
        return false;
    }

    // 添加地图到当前节点
    this->addChild(_tile_map, 0);
    this->setPosition(_map_position);

    return true;
}

// 转换世界坐标到地图瓦片坐标
Vec2 GameMap::absoluteToTile(const Vec2& pixelPoint)
{
    if (!_implementation) {
        return Vec2::ZERO;
    }
    return _implementation->absoluteToTile(_tile_map, _map_position, this->getScale(), pixelPoint);
}

// 转换瓦片坐标到世界坐标（中点）
Vec2 GameMap::tileToAbsolute(const Vec2& tileCoord)
{
    if (!_implementation) {
        return Vec2::ZERO;
    }
    return _implementation->tileToAbsolute(_tile_map, _map_position, this->getScale(), tileCoord);
}

Vec2 GameMap::tileToRelative(const Vec2& tileCoord)
{
    if (!_implementation) {
        return Vec2::ZERO;
    }
    return _implementation->tileToRelative(_tile_map, _map_position, tileCoord);
}

// 地图像素大小
const Size& GameMap::getMapSize() const
{
    Size map_size_in_tiles = _tile_map->getMapSize();
    Size tile_size = _tile_map->getTileSize();

    float map_width_in_pixels = map_size_in_tiles.width * tile_size.width;
    float map_height_in_pixels = map_size_in_tiles.height * tile_size.height;

    return Size(map_width_in_pixels, map_height_in_pixels);
}

// 地图瓦片大小
const Size& GameMap::getMapSizeinTile()
{
    return _tile_map->getMapSize();
}

// 地图绝对位置
const Vec2& GameMap::getPosition() {
    return _map_position;
}

// 获取某位置Layername图层的GID
int GameMap::getTileGIDAt(const std::string& layerName, const Vec2& tileCoord) const
{
    if (!_implementation) {
        return 0;
    }
    return _implementation->getTileGIDAt(_tile_map, layerName, tileCoord);
}

// 获取某GID对应图块的属性
cocos2d::ValueMap GameMap::getTilePropertiesForGID(int GID) const
{
    if (!_implementation) {
        return cocos2d::ValueMap();
    }
    return _implementation->getTilePropertiesForGID(_tile_map, GID);
}

// 替换指定图层的瓦片
void GameMap::replaceTileAt(const std::string& layerName, const Vec2& tileCoord, int newGID, bool isUserAction) {
    if (_implementation) {
        _implementation->replaceTileAt(_tile_map, layerName, tileCoord, newGID);
    }
    // 如果是用户行为保存修改，如果是恢复更改时不保存避免重复保存导致死循环
    if(isUserAction)
    {
        // 保存到 MapStateManager
        MapStateManager::getInstance().saveTileChange(_mapName, TileConstants::TileChange(layerName, tileCoord, newGID));
    }
}
// 获取地图指针
TMXTiledMap* GameMap::getTiledMap() const {
    return _tile_map;
}

//获取节点指针
Node* GameMap::getNodeAtPosition(const Vec2& tilePos) {
    return nullptr; // 默认返回 nullptr
}

// 恢复存储的文档
void GameMap::applySavedChanges() {
    const auto& changes = MapStateManager::getInstance().getTileChanges(_mapName);
    for (const auto& change : changes) {
        replaceTileAt(change.layerName, change.tileCoord, change.newGID, false);
    }
    CCLOG("Applied %zu saved tile changes for map '%s'.", changes.size(), _mapName.c_str());
}

// 当前地图保存已经在嫦changeTileInfo时保存，保留此方法是为了后续保存其他内容时候使用
void GameMap::saveChangesToStateManager() const {
    // 保存地图瓦片的更改逻辑
    const auto& changes = MapStateManager::getInstance().getTileChanges(_mapName);
    for (const auto& change : changes) {
        CCLOG("Saving tile change: Layer='%s', Tile=(%f, %f), GID=%d",
            change.layerName.c_str(), change.tileCoord.x, change.tileCoord.y, change.newGID);
    }

    CCLOG("Saved %zu changes for map: %s", changes.size(), _mapName.c_str());
}



