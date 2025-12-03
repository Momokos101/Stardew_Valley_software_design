/****************************************************************
 * Project Name:  Stardew_Valley
 * File Name:     NullNPC.h
 * File Function: Null Object Pattern 实现 - 空 NPC 对象
 *                用于替代 nullptr，消除空指针检查，提升代码安全性
 * Author:        AI-Assistant
 * Update Date:   2024/12/22
 * License:       MIT License
 ****************************************************************/
#pragma once
#ifndef NULL_NPC_H
#define NULL_NPC_H

#include "Character/NPC.h"
#include "cocos2d.h"

/**
 * NullNPC - 空对象模式实现
 * 
 * 设计模式：Null Object Pattern（空对象模式）
 * 
 * 用途：
 * - 当 NpcManager::getNPCByName() 找不到指定 NPC 时，返回 NullNPC 实例而非 nullptr
 * - 消除调用方的空指针检查，使代码更简洁、更安全
 * - 提供"什么都不做"的默认行为，避免程序崩溃
 * 
 * 参考：https://en.wikipedia.org/wiki/Null_object_pattern
 */
class NullNPC : public NPC {
public:
    // 获取单例实例（Null Object 通常使用单例）
    static NullNPC* getInstance();
    
    // 重写所有 NPC 方法，提供"空操作"实现
    void showDialog() override;
    void showDialogue(const std::string& dialogueText) override;
    void increaseAffection(int value) override;
    void marryPlayer() override;
    void playMarriageAnimation() override;
    void showMarriageChoices() override;
    void giftItem(GiftItem* gift) override;
    void moveTo(cocos2d::Vec2 targetPosition) override;
    void startWalkingAnimation() override;
    void addTask(Task* task) override;
    void showTaskList() override;
    void setIsProcessing(bool isProcessing) override;
    
    // TimeObserver 接口实现（空操作）
    void onDayChanged(int day) override;
    void onSeasonChanged(Season season) override;
    void onTimeChanged(int hour, int minute) override;
    
    // 检查是否为 Null Object
    bool isNull() const { return true; }
    
private:
    NullNPC();  // 私有构造函数，强制使用单例
    ~NullNPC() = default;
    
    static NullNPC* _instance;  // 单例实例
};

#endif // NULL_NPC_H

