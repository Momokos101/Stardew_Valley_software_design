/****************************************************************
 * Project Name:  Stardew_Valley
 * File Name:     TimeObserver.h
 * File Function: 时间观察者接口定义
 * Author:        AI-Assistant
 * Update Date:   2024/12/22
 * License:       MIT License
 ****************************************************************/
#pragma once
#ifndef __TIME_OBSERVER_H__
#define __TIME_OBSERVER_H__

#include "proj.win32/Constant.h"

// 时间系统观察者接口
class TimeObserver {
public:
    virtual ~TimeObserver() = default;

    // 天数改变时回调（如从第 day-1 天变为第 day 天）
    virtual void onDayChanged(int day) = 0;

    // 季节改变时回调
    virtual void onSeasonChanged(Season season) = 0;

    // 时间（小时/分钟）改变时回调
    virtual void onTimeChanged(int hour, int minute) = 0;
};

#endif // !__TIME_OBSERVER_H__


