/****************************************************************
 * Project Name:  Stardew_Valley
 * File Name:     NullNPC.cpp
 * File Function: Null Object Pattern 实现 - 空 NPC 对象
 * Author:        AI-Assistant
 * Update Date:   2024/12/22
 * License:       MIT License
 ****************************************************************/

#include "NullNPC.h"
#include "Character/Task.h"
#include "Character/GiftItem.h"
#include <cocos2d.h>

USING_NS_CC;

// 静态成员初始化
NullNPC* NullNPC::_instance = nullptr;

// 私有构造函数：创建一个不可见的、位置为 (0,0) 的空 NPC
NullNPC::NullNPC() 
    : NPC("", Vec2::ZERO, "", std::vector<std::string>()) {
    // 设置为不可见，避免在场景中显示
    this->setVisible(false);
}

// 获取单例实例
NullNPC* NullNPC::getInstance() {
    if (!_instance) {
        _instance = new NullNPC();
        // 注意：NullNPC 作为单例，生命周期与程序相同，不需要手动释放
        // 如果需要，可以在程序退出时统一清理
    }
    return _instance;
}

// 所有方法都提供"空操作"实现，避免程序崩溃
void NullNPC::showDialog() {
    // 空操作：不显示任何对话框
    CCLOG("NullNPC::showDialog() - No NPC found, operation ignored.");
}

void NullNPC::showDialogue(const std::string& dialogueText) {
    // 空操作：不显示任何对话
    CCLOG("NullNPC::showDialogue() - No NPC found, dialogue ignored.");
}

void NullNPC::increaseAffection(int value) {
    // 空操作：不增加任何好感度
    CCLOG("NullNPC::increaseAffection() - No NPC found, affection change ignored.");
}

void NullNPC::marryPlayer() {
    // 空操作：不执行结婚逻辑
    CCLOG("NullNPC::marryPlayer() - No NPC found, marriage operation ignored.");
}

void NullNPC::playMarriageAnimation() {
    // 空操作：不播放任何动画
    CCLOG("NullNPC::playMarriageAnimation() - No NPC found, animation ignored.");
}

void NullNPC::showMarriageChoices() {
    // 空操作：不显示结婚选择框
    CCLOG("NullNPC::showMarriageChoices() - No NPC found, choices ignored.");
}

void NullNPC::giftItem(GiftItem* gift) {
    // 空操作：不接受任何礼物
    CCLOG("NullNPC::giftItem() - No NPC found, gift ignored.");
}

void NullNPC::moveTo(cocos2d::Vec2 targetPosition) {
    // 空操作：不移动
    CCLOG("NullNPC::moveTo() - No NPC found, movement ignored.");
}

void NullNPC::startWalkingAnimation() {
    // 空操作：不播放行走动画
    CCLOG("NullNPC::startWalkingAnimation() - No NPC found, animation ignored.");
}

void NullNPC::addTask(Task* task) {
    // 空操作：不添加任务
    CCLOG("NullNPC::addTask() - No NPC found, task ignored.");
}

void NullNPC::showTaskList() {
    // 空操作：不显示任务列表
    CCLOG("NullNPC::showTaskList() - No NPC found, task list ignored.");
}

void NullNPC::setIsProcessing(bool isProcessing) {
    // 空操作：不改变处理状态
    CCLOG("NullNPC::setIsProcessing() - No NPC found, state change ignored.");
}

// TimeObserver 接口实现（空操作）
void NullNPC::onDayChanged(int day) {
    // 空操作：不响应日期变化
}

void NullNPC::onSeasonChanged(Season season) {
    // 空操作：不响应季节变化
}

void NullNPC::onTimeChanged(int hour, int minute) {
    // 空操作：不响应时间变化
}

