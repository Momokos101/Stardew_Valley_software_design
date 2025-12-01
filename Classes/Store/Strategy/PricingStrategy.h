/****************************************************************
 * Project Name:  Stardew_Valley
 * File Name:     PricingStrategy.h
 * File Function: 商店价格策略基类
 * Author:        AI-Assistant
 * Update Date:   2024/12/22
 * License:       MIT License
 ****************************************************************/
#pragma once
#ifndef __PRICING_STRATEGY_H__
#define __PRICING_STRATEGY_H__

#include <memory>
#include "proj.win32/Constant.h"
#include "Control/TimeManager.h"

// 价格策略基类
class PricingStrategy {
public:
    virtual ~PricingStrategy() = default;

    // 对单个商品应用价格策略（原地修改 totalPrice）
    virtual void apply(ProductNode& product, const TimeManager& timeManager) = 0;
};

#endif // !__PRICING_STRATEGY_H__


