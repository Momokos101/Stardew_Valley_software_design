/****************************************************************
 * Project Name:  Stardew_Valley
 * File Name:     SeasonalPricingStrategy.h
 * File Function: 按季节打折/涨价的价格策略
 * Author:        AI-Assistant
 * Update Date:   2024/12/22
 * License:       MIT License
 ****************************************************************/
#pragma once
#ifndef __SEASONAL_PRICING_STRATEGY_H__
#define __SEASONAL_PRICING_STRATEGY_H__

#include "Store/Strategy/PricingStrategy.h"

class SeasonalPricingStrategy : public PricingStrategy {
public:
    void apply(ProductNode& product, const TimeManager& timeManager) override;
};

#endif // !__SEASONAL_PRICING_STRATEGY_H__


