
/****************************************************************
 * Project Name:  Stardew_Valley
 * File Name:     NpcManager.cpp
 * File Function: 管理游戏中的 NPC 实例，负责创建、查询与对话等功能
 * Author:        ��˼�
 * Update Date:   2024/12/22
 * License:       MIT License
 ****************************************************************/
#include "NpcManager.h"
#include "Control/TimeManager.h"

// 构造函数
NpcManager::NpcManager() {}

// 析构函数
NpcManager::~NpcManager() {
    // 从时间管理器注销所有 NPC 观察者
    TimeManager* timeManager = TimeManager::getInstance();
    if (timeManager) {
        for (auto npc : _npcs) {
            timeManager->detach(npc);
        }
    }

    for (auto npc : _npcs) {
        delete npc;
    }
    _npcs.clear();
}

// 获取单例
NpcManager* NpcManager::getInstance() {
    static NpcManager* _instance = nullptr;
    if (!_instance) {
        _instance = new NpcManager();
    }
    return _instance;
}

// 初始化 NPC
void NpcManager::initializeNPCs() {
    // 初始化 NPC 实例，并添加到列表
    NPC* npc1 = new NPC("Abigail", cocos2d::Vec2(100, 160),
        "../Resources/Characters/NPC/Abigail_1.png",
        { "../Resources/Characters/NPC/Abigail_1.png",
          "../Resources/Characters/NPC/Abigail_2.png",
          "../Resources/Characters/NPC/Abigail_3.png",
          "../Resources/Characters/NPC/Abigail_4.png" });
    npc1->_dialogues = {
        "Hello, traveler",
        "I feel like you care about me",
        "Thank you for the gift"
    };
    // 为 Abigail 添加两个任务
    Task* task1 = new Task("Give me a gift (I like pumpkin)", "pumpkin", 1, 10);
    Task* task2 = new Task("Help me repair the building.", "Timber", 4, 20);

    npc1->addTask(task1);
    npc1->addTask(task2);
    _npcs.push_back(npc1);

    NPC* npc2 = new NPC("Mary", cocos2d::Vec2(300, 200),
        "../Resources/Characters/NPC/Abigail_1.png",
        { "../Resources/Characters/NPC/Abigail_1.png",
          "../Resources/Characters/NPC/Abigail_2.png" });
    npc2->_dialogues = {
        "Welcome",
        "You are a kind person",
        "I appreciate your thoughtfulness"
    };
    _npcs.push_back(npc2);

    // 将所有 NPC 注册为时间观察者
    TimeManager* timeManager = TimeManager::getInstance();
    if (timeManager) {
        for (auto npc : _npcs) {
            timeManager->attach(npc);
        }
    }
}

// 根据名字获取 NPC
NPC* NpcManager::getNPCByName(const std::string& name) {
    for (auto npc : _npcs) {
        if (npc->getName() == name) {
            return npc;
        }
    }
    return nullptr;
}

// 显示 NPC 对话
void NpcManager::showDialog(NPC* npc) {
    if (npc) {
        npc->showDialog();
    }
}
