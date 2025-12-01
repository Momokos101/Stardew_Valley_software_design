/****************************************************************
 * Project Name:  Stardew_Valley
 * File Name:     MapSwitchManager.cpp
 * File Function: ��ͼ�л�������MapSwitchManager��ʵ��
 * Author:        �����
 * Update Date:   2024/12/11
 * License:       MIT License
 ****************************************************************/
#include "MapSwitchManager.h"

MapSwitchManager::MapSwitchManager()
    : _character(nullptr), _currentMap(nullptr), _viewController(nullptr) {}

MapSwitchManager* MapSwitchManager::create(Character* character, GameMap* currentMap, GameViewController* viewController,InteractionManager* interactionManager) {
    MapSwitchManager* ret = new (std::nothrow) MapSwitchManager();
    if (ret && ret->init(character, currentMap, viewController, interactionManager)) {
        ret->autorelease();
        return ret;
    }
    CC_SAFE_DELETE(ret);
    return nullptr;
}

bool MapSwitchManager::init(Character* character, GameMap* currentMap, GameViewController* viewController, InteractionManager* interactionManager) {
    if (!Node::init()) {
        return false;
    }

    CCASSERT(character != nullptr, "Character must not be null");
    CCASSERT(currentMap != nullptr, "Current map must not be null");
    CCASSERT(viewController != nullptr, "GameViewController must not be null");
    CCASSERT(interactionManager != nullptr, "InteractionManager must not be null");

    _character = character;
    _currentMap = currentMap;
    _viewController = viewController;
    _interactionManager = interactionManager;

    return true;
}

bool MapSwitchManager::switchMap(const std::string& newMapFile, Vec2& teleportPOS, Node* TreeLayer,Node* MapLayer) {
    CCLOG("Switching map to: %s", newMapFile.c_str());

    // �����ƹ�Ч����RAII ���Զ����پɵƹ⣩
    _lightingGuard.reset();

    if (_currentMap) {
        // ���浱ǰ��ͼ״̬
        _currentMap->saveChangesToStateManager();
        MapLayer->removeChild(_currentMap, true); // �����ɵ�ͼ
    }
    

    GameMap* newMap = nullptr;

    if (newMapFile.find("Combat") != std::string::npos) {
        // 农场地图
        newMap = _farmAdapter.createAndAttachMap(newMapFile, TreeLayer, MapLayer);
        teleportPOS = _farmAdapter.getTeleportPosition(newMap);
    }
    else if (newMapFile.find("house") != std::string::npos) {
        // 室内地图（农场房子）
        newMap = _indoorAdapter.createAndAttachMap(newMapFile, nullptr, MapLayer);
        teleportPOS = _indoorAdapter.getTeleportPosition(newMap);
    }
    else if (newMapFile.find("Town") != std::string::npos) {
        // 小镇地图
        newMap = _townAdapter.createAndAttachMap(newMapFile, nullptr, MapLayer);
        teleportPOS = _townAdapter.getTeleportPosition(newMap);
    }
    else if (newMapFile.find("Mine") != std::string::npos) {
        // 矿洞地图
        newMap = _mineAdapter.createAndAttachMap(newMapFile, nullptr, MapLayer);
        teleportPOS = _mineAdapter.getTeleportPosition(newMap);
        if (newMap) {
            // 为矿洞地图添加灯光效果
            _lightingGuard = std::make_unique<IndoorLighting>(newMap);
        }
    }
    else {
        CCLOG("Unknown map type for file: %s", newMapFile.c_str());
        return false;
    }

    if (!newMap) {
        CCLOG("Failed to create map: %s", newMapFile.c_str());
        return false;
    }

    _currentMap = newMap;
    _currentMap->applySavedChanges();

    // ���� InteractionManager �ĵ�ͼ����
    if (_interactionManager) {
        _interactionManager->setMap(_currentMap);
        CCLOG("InteractionManager map updated.");
    }

    // �����ӽǿ������ĵ�ͼ����
    if (_viewController) {
        _viewController->setMap(_currentMap);
        CCLOG("GameViewController map updated.");
    }

    return true;
}




