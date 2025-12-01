/****************************************************************
 * Project Name:  Stardew_Valley
 * File Name:     SeasonalPricingStrategy.cpp
 * File Function: 按季节打折/涨价的价格策略实现
 * Author:        AI-Assistant
 * Update Date:   2024/12/22
 * License:       MIT License
 ****************************************************************/
#include "Store/Strategy/SeasonalPricingStrategy.h"

void SeasonalPricingStrategy::apply(ProductNode& product, const TimeManager& timeManager) {
    Season currentSeason = timeManager.getCurrentSeason();

    if (product.discountSeason != Season::All && product.discountSeason == currentSeason) {
        product.totalPrice = static_cast<int>(product.totalPrice * DISCOUNT_RATE_BY_SEASON);
    }
    else if (product.increaseSeason != Season::All && product.increaseSeason == currentSeason) {
        product.totalPrice = static_cast<int>(product.totalPrice * INCREASE_RATE_BY_SEASON);
    }
}


