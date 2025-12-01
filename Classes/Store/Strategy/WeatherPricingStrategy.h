/****************************************************************
 * Project Name:  Stardew_Valley
 * File Name:     WeatherPricingStrategy.h
 * File Function: 按天气调整价格的策略
 * Author:        AI-Assistant
 * Update Date:   2024/12/22
 * License:       MIT License
 ****************************************************************/
#pragma once
#ifndef __WEATHER_PRICING_STRATEGY_H__
#define __WEATHER_PRICING_STRATEGY_H__

#include "Store/Strategy/PricingStrategy.h"

class WeatherPricingStrategy : public PricingStrategy {
public:
    void apply(ProductNode& product, const TimeManager& timeManager) override;
};

#endif // !__WEATHER_PRICING_STRATEGY_H__


