/****************************************************************
 * Project Name:  Stardew_Valley
 * File Name:     WeatherPricingStrategy.cpp
 * File Function: 按天气调整价格的策略实现
 * Author:        AI-Assistant
 * Update Date:   2024/12/22
 * License:       MIT License
 ****************************************************************/
#include "Store/Strategy/WeatherPricingStrategy.h"

void WeatherPricingStrategy::apply(ProductNode& product, const TimeManager& timeManager) {
    // 简单示例：雨天农作物价格略微上升，干燥天气略微下降
    Weather weather = timeManager.getCurrentWeather();

    if (product.product.type == GameObjectMapType::Seed ||
        product.product.type == GameObjectMapType::Base) {
        if (weather == Weather::Rainy) {
            product.totalPrice = static_cast<int>(product.totalPrice * 1.05f);
        }
        else if (weather == Weather::Dry) {
            product.totalPrice = static_cast<int>(product.totalPrice * 0.95f);
        }
    }
}


