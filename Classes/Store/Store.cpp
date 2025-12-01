/****************************************************************
 * Project Name:  Stardew_Valley
 * File Name:     Store.cpp
 * File Function: 商店 Store 类实现（集成 Observer + Strategy 模式）
 * Author:        尹诚成 + AI-Assistant
 * Update Date:   2024/12/22
 * License:       MIT License
 ****************************************************************/

#include "Store.h"
#include "Store/Strategy/SeasonalPricingStrategy.h"
#include "Store/Strategy/WeatherPricingStrategy.h"
#include "Store/Strategy/AffectionPricingStrategy.h"

// 获取单例
Store* Store::getInstance() {
	static Store instance;
	return &instance;
}

// 构造函数
Store::Store()
	: _character(Character::getInstance()),
	  _timeManager(TimeManager::getInstance()),
	  productKindCount(PRODUCE_KIND_NUM_EACH_DAY) {

	_product.clear();

	// 注册到时间管理器，作为观察者
	if (_timeManager) {
		_timeManager->attach(this);
	}

	// 初始化价格策略
	_pricingStrategies.push_back(new SeasonalPricingStrategy());
	_pricingStrategies.push_back(new WeatherPricingStrategy());
	_pricingStrategies.push_back(new AffectionPricingStrategy());
}

// 析构函数
Store::~Store() {
	if (_timeManager) {
		_timeManager->detach(this);
	}
	for (auto* strategy : _pricingStrategies) {
		delete strategy;
	}
	_pricingStrategies.clear();
}

// 新的一天刷新商店货物
void Store::refreshStock() {
	_product.clear();
	int seedProductKind = rand() % PRODUCE_KIND_NUM_EACH_DAY + 1;	// 随机种子类商品种类数
	int baseProductKind = PRODUCE_KIND_NUM_EACH_DAY - seedProductKind;

	// 生成种子类商品（根据玩家技能等级筛选）
	for (int i = 0; i < seedProductKind; i++) {
		int seedIndex = INVAVID_NUM;
		do {
			seedIndex = rand() % GAME_SEED_OBJECTS_ATTRS.size();
		} while (!(_character->getSkillLevel(GAME_SEED_OBJECTS_ATTRS[seedIndex]._type) >= GAME_SEED_OBJECTS_ATTRS[seedIndex]._level));

		int productCount = rand() % MAX_PRODUCT_COUNT_EACH_DAY + 1;
		std::shared_ptr<GameObject> targetObjectPtr = std::make_shared<GameSeedObject>(GAME_SEED_OBJECTS_ATTRS[seedIndex]);
		GameCommonObject commonObject(GameObjectMapType::Seed, targetObjectPtr);
		_product.push_back(ProductNode{ commonObject,
										productCount,
										productCount * GAME_SEED_OBJECTS_ATTRS[seedIndex]._buyPrice,
										GAME_SEED_OBJECTS_ATTRS[seedIndex]._season,
										static_cast<Season>((GAME_SEED_OBJECTS_ATTRS[seedIndex]._season + 2) % 4) });
	}

	// 生成基础类商品
	for (int i = seedProductKind; i < productKindCount; i++) {
		int baseIndex = INVAVID_NUM;
		do {
			baseIndex = rand() % GAME_BASE_OBJECTS_ATTRS.size();
		} while (!(GAME_BASE_OBJECTS_ATTRS[baseIndex]._buy
			&& (_character->getSkillLevel(GAME_BASE_OBJECTS_ATTRS[baseIndex]._type) >= GAME_BASE_OBJECTS_ATTRS[baseIndex]._level)));

		int productCount = rand() % MAX_PRODUCT_COUNT_EACH_DAY + 1;
		std::shared_ptr<GameObject> targetObjectPtr = std::make_shared<GameBaseObject>(GAME_BASE_OBJECTS_ATTRS[baseIndex]);
		GameCommonObject commonObject(GameObjectMapType::Base, targetObjectPtr);

		GameSeedObject seedObject;
		if (canHarvestFromAnySeed(GAME_BASE_OBJECTS_ATTRS[baseIndex], seedObject)) {
			_product.push_back(ProductNode{ commonObject,
											productCount,
											productCount * GAME_BASE_OBJECTS_ATTRS[baseIndex]._buyPrice,
											seedObject._season,
											static_cast<Season>((seedObject._season + 2) % 4) });
		}
		else {
			_product.push_back(ProductNode{ commonObject,
											productCount,
											productCount * GAME_BASE_OBJECTS_ATTRS[baseIndex]._buyPrice,
											Season::All,
											Season::All });
		}
	}

	// 按策略更新价格
	updatePrices();
}

// 购买商品
bool Store::buyProduct(int index) {
	int characterMoney = _character->getMoney();
	if (index < 0 || index >= static_cast<int>(_product.size())) {
		return false;
	}
	if (characterMoney < _product[index].totalPrice) {
		return false;
	}
	else if (_product[index].product.type == None) {
		return false;
	}

	if (_character->pickUpObject(_product[index].product, _product[index].count) == true) {
		_character->setMoney(_product[index].totalPrice * -1);
		_product[index] = { { None, nullptr }, 0, 0, Season::All, Season::All };
		return true;
	}
	return false;
}

// 出售商品
bool Store::sellProduct(const GameCommonObject targetObject, int objectCount) {
	int salePrice = 0;
	if (targetObject.type == Tool) {
		return false;
	}
	else if (targetObject.type == Seed) {
		GameSeedObject* seedObject = dynamic_cast<GameSeedObject*>(_character->getCurrentObject().objectNode.object.get());
		if (!seedObject) return false;
		salePrice = seedObject->_sellPrice;
	}
	else if (targetObject.type == Base) {
		GameBaseObject* baseObject = dynamic_cast<GameBaseObject*>(_character->getCurrentObject().objectNode.object.get());
		if (!baseObject || baseObject->_sell == false) {
			return false;
		}
		salePrice = baseObject->_sellPrice;
	}
	_character->deleteCurrentObject();
	_character->setMoney(objectCount * salePrice);
	if (_sellProductCallback) {
		_sellProductCallback(true);
	}
	return true;
}

// 查找指定位置的商品信息
ProductNode Store::findObjectAtPosition(int index) {
	if (index < 0 || index >= static_cast<int>(_product.size())) {
		return ProductNode();
	}

	return _product[index];
}

// 设置出售回调
void Store::setSellProductCallback(std::function<void(bool)> callback) {
	_sellProductCallback = callback;
}

// 使用策略更新价格
void Store::updatePrices() {
	if (!_timeManager) {
		_timeManager = TimeManager::getInstance();
	}
	if (!_timeManager) return;

	for (auto& product : _product) {
		for (auto* strategy : _pricingStrategies) {
			if (strategy) {
				strategy->apply(product, *_timeManager);
			}
		}
	}

	// 保留原有的星期四统一折扣逻辑
	std::string weekDay = _timeManager->getWeekDay();
	if (weekDay == "Thursday") {
		for (auto& product : _product) {
			product.totalPrice = static_cast<int>(product.totalPrice * DISCOUNT_RATE_BY_SEASON);
		}
	}
}

// 判断商品是否为某种种子的收获物
bool Store::canHarvestFromAnySeed(const GameBaseObject& baseObject, GameSeedObject& seedObject) {
	for (const auto& seed : GAME_SEED_OBJECTS_ATTRS) {
		if (baseObject._index == seed._harvestIndex) {
			seedObject = seed;
			return true;
		}
	}
	return false;
}

// TimeObserver: 新的一天
void Store::onDayChanged(int /*day*/) {
	// 新的一天刷新货物，并重新计算价格
	refreshStock();
}

// TimeObserver: 季节变化
void Store::onSeasonChanged(Season /*season*/) {
	// 仅重新计算价格
	updatePrices();
}

// TimeObserver: 时间变化（当前未使用，可根据需求扩展）
void Store::onTimeChanged(int /*hour*/, int /*minute*/) {
	// 暂不根据小时/分钟动态调整价格
}

