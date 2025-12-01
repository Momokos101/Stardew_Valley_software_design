/****************************************************************
 * Project Name:  Stardew_Valley
 * File Name:     Store.h
 * File Function: 商店Store类的定义
 * Author:        尹诚成
 * Update Date:   2024/12/20
 * License:       MIT License
 ****************************************************************/

#pragma once
#ifndef __STORE_H__
#define __STORE_H__

#include <string>
#include <vector>
#include <map>
#include <functional>
#include "Character/Character.h"
#include "Control/TimeManager.h"
#include "Control/Observer/TimeObserver.h"
#include "Store/Strategy/PricingStrategy.h"

// 商店类：实现时间观察者 + 价格策略模式
class Store : public TimeObserver {
public:
	// 获取单例
	static Store* getInstance();

	// 新的一天刷新商店货物
	void refreshStock();

	// 购买商品
	bool buyProduct(int index);

	// 出售商品
	bool sellProduct(const GameCommonObject targetObject, int objectCount);

	// 查找指定位置的商品信息
	ProductNode findObjectAtPosition(int index);

	// 出售完成回调
	void setSellProductCallback(std::function<void(bool)> callback);

	// TimeObserver 接口实现
	void onDayChanged(int day) override;
	void onSeasonChanged(Season season) override;
	void onTimeChanged(int hour, int minute) override;

	std::function<void(bool)> _sellProductCallback;  // 用于保存回调

private:
	Character* _character;					 // 玩家角色
	TimeManager* _timeManager;				 // 时间管理器
	int productKindCount;					 // 商店每天售卖的货物种类
	std::vector<ProductNode> _product;		 // 商品种类及数量
	std::vector<PricingStrategy*> _pricingStrategies; // 价格策略列表

	// 构造/析构
	Store();
	~Store();

	// 判断物品是否是种子的收获物
	bool canHarvestFromAnySeed(const GameBaseObject& baseObject, GameSeedObject& seedObject);

	// 使用策略更新所有商品价格
	void updatePrices();

	// TODO：根据好感度更新价格（可在 AffectionPricingStrategy 中扩展）
	// void updatePricesByLove();
};

#endif // !__STORE_H__