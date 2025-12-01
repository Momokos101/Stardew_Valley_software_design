/****************************************************************
 * Project Name:  Stardew_Valley
 * File Name:     TimeManager.cpp
 * File Function: ��Ϸ��ʱ�����TimeManager�Ķ���
 * Author:        ��˼�
 * Update Date:   2024/12/21
 * License:       MIT License
 ****************************************************************/
#pragma once
#ifndef __TIMEMANAGER_H__
#define __TIMEMANAGER_H__

#include "cocos2d.h"
#include "proj.win32/Constant.h"
#include "Observer/TimeObserver.h"
#include <vector>

// 时间管理器：负责全局游戏时间，并作为 Observer 模式中的 Subject
class TimeManager {
public:
    // 获取 TimeManager 的单例
    static TimeManager* getInstance();

    // 更新时间（以“游戏秒”为单位推进）
    void update(int deltaT);

    // 获取当前星期几，例如：Monday, Tuesday...
    std::string getWeekDay() const;

    // 获取当前时间（小时:分钟，字符串格式）
    std::string getCurrentTime() const;

    // 获取当前季节
    Season getCurrentSeason() const;

    // 获取当前季节的字符串表示
    std::string getCurrentSeasonStr() const;

    // 获取当前游戏天数
    int getCurrentDay() const;

    // 获取当前天气
    Weather getCurrentWeather() const;

    // 获取当前天气的字符串表示
    std::string getCurrentWeatherStr() const;

    // 判断当前是否为白天
    bool isDaytime() const;

    // 开始时间更新
    void startUpdating();

    // 停止时间更新
    void stopUpdating();

    // Observer 注册/注销
    void attach(TimeObserver* observer);
    void detach(TimeObserver* observer);

    // 主动通知（通常由 TimeManager 内部调用）
    void notifyDayChanged(int day);
    void notifySeasonChanged(Season season);
    void notifyTimeChanged(int hour, int minute);

private:
    // 构造函数
    TimeManager();

    // 析构函数
    ~TimeManager();

    // 计算当前的小时、分钟、天数
    void updateTime();

    // 更新昼夜状态
    void updateDayNightCycle();

    // 更新季节
    void updateSeason();

    // 随机更新天气
    void updateWeather();

    int _timeInSeconds;   // 游戏中的时间（以“小时”为单位的累积值）
    int _day;             // 当前游戏天数
    int _hour;            // 当前小时
    int _minute;          // 当前分钟
    Season _season;       // 当前季节
    Weather _weather;     // 当前天气
    bool _isDay;          // 是否为白天

    // 观察者列表
    std::vector<TimeObserver*> _observers;
};

#endif // ! __TIMEMANAGER_H__