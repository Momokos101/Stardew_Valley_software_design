/****************************************************************
 * Project Name:  Stardew_Valley
 * File Name:     GameMap.h
 * File Function: 地图基类 GameMap 的定义（作为 Bridge 模式中的抽象层）
 * Author:        �����
 * Update Date:   2024/12/11
 * License:       MIT License
 ****************************************************************/
#pragma once
#ifndef GAME_MAP_H_
#define GAME_MAP_H_

#include "cocos2d.h"
#include "Crops/Crops.h"
#include "Control/MapStateManager.h"
#include <memory>

USING_NS_CC;

class MapImplementation;

class GameMap : public Node {
public:
    GameMap(const Vec2& mapPosition = Vec2(0, 0));

    virtual ~GameMap();

    // ������ͼ
    virtual GameMap* create(const std::string& mapFile, const Vec2& mapPosition = Vec2(0, 0));

    // ��ʼ����ͼ
    virtual bool init(const std::string& mapFile, const Vec2& mapPosition);

    // ת���������굽��ͼ��Ƭ����
    virtual Vec2 absoluteToTile(const Vec2& pixelPoint);

    // ת����Ƭ���굽�������꣨�е㣩
    Vec2 tileToAbsolute(const Vec2& tileCoord);

    // ת����Ƭ���굽�Ե�ͼΪ���ڵ��������꣨�е㣩
    Vec2 tileToRelative(const Vec2& tileCoord);

    // ��ͼ���ش�С
    const Size& getMapSize() const;

    // ��ͼ��Ƭ��С
    const Size& getMapSizeinTile();

    // ��ͼ����λ��
    const Vec2& GameMap::getPosition();

    // ��ȡĳλ��Layernameͼ���GID
    int getTileGIDAt(const std::string& layerName, const Vec2& tileCoord) const ;

    // ��ȡĳGID��Ӧͼ�������
    cocos2d::ValueMap getTilePropertiesForGID(int GID) const;

    // �滻ָ��ͼ�����Ƭ���ڿ�����ʵ��ˢ���߼���¼
    virtual void replaceTileAt(const std::string& layerName, const Vec2& tileCoord, int newGID, bool isUserAction = true);

    // ��ȡ��ͼ�Ͻڵ��ָ���麯��
    virtual Node* getNodeAtPosition(const Vec2& tilePos);

    // ��ȡ��Ƭ��ͼָ��
    TMXTiledMap* getTiledMap() const;

    // �ָ��洢�ĵ�ͼ��Ϣ
    virtual void applySavedChanges();

    // �����ͼ��Ϣ���麯����Ϊ�˷�ֹ������������Ҫ�������Ϣ
    virtual void saveChangesToStateManager() const;

    // ��ͼ����
    virtual MapType getType() const { return MapType::Generic; }
protected:
    std::string _mapName;     // ��ͼ�ļ���
    TMXTiledMap* _tile_map;  // ��Ƭ��ͼ��
    Vec2 _map_position;      // ��ͼ����λ��

    // Bridge 模式中的实现部分
    std::unique_ptr<MapImplementation> _implementation;
};

#endif // GAME_MAP_H_
