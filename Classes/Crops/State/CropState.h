/****************************************************************
 * Project Name:  Stardew_Valley
 * File Name:     CropState.h
 * File Function: 农作物状态基类（State 模式）
 * Author:        AI-Assistant
 * Update Date:   2024/12/22
 * License:       MIT License
 ****************************************************************/
#pragma once
#ifndef __CROP_STATE_H__
#define __CROP_STATE_H__

class Crops;

// 农作物状态基类
class CropState {
public:
    virtual ~CropState() = default;

    // 生长更新（当前项目中仍由 Crops 主导，此接口保留扩展点）
    virtual void update(Crops* /*crop*/, float /*deltaTime*/) {}

    // 浇水行为（当前项目中由 Crops::waterCrop 实现，此接口保留扩展点）
    virtual void water(Crops* /*crop*/) {}

    // 是否可以收获
    virtual bool canHarvest(const Crops* crop) const = 0;
};

#endif // !__CROP_STATE_H__


