/****************************************************************
 * Project Name:  Stardew_Valley
 * File Name:     AffectionPricingStrategy.h
 * File Function: 按好感度调整价格的策略（示意实现，可扩展）
 * Author:        AI-Assistant
 * Update Date:   2024/12/22
 * License:       MIT License
 ****************************************************************/
#pragma once
#ifndef __AFFECTION_PRICING_STRATEGY_H__
#define __AFFECTION_PRICING_STRATEGY_H__

#include "Store/Strategy/PricingStrategy.h"

// 当前项目中没有统一的“好感度到折扣”接口，这里保留策略类，逻辑可后续扩展
class AffectionPricingStrategy : public PricingStrategy {
public:
    void apply(ProductNode& product, const TimeManager& timeManager) override;
};

#endif // !__AFFECTION_PRICING_STRATEGY_H__


