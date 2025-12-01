/****************************************************************
 * Project Name:  Stardew_Valley
 * File Name:     Crops.h
 * File Function: ũ�����࣬ʵ��ũ����ĸ��ֻ�������
 * Author:        ������
 * Update Date:   2024/12/22
 * License:       MIT License
 ****************************************************************/
#include "Crops.h"
#include "Classes/Control/TimeManager.h"
#include "Crops/State/CropState.h"
#include "Crops/State/SeedState.h"
#include "Crops/State/SproutingState.h"
#include "Crops/State/GrowingState.h"
#include "Crops/State/MatureState.h"

USING_NS_CC;
// ��ʼ����̬����
Season Crops::_currentSeason = Season::Spring;
int Crops::_playerLevel = 1; // ��ʼ����ȼ�Ϊ1

// ���徲̬��Դӳ���
std::unordered_map<std::string, std::vector<std::string>> Crops::_resourceMap;

void Crops::initializeResourceMap() {
    // �����Դ���Ѿ���ʼ����������
    if (!_resourceMap.empty()) return;

    // Ϊÿ��ũ�����������Ӷ�Ӧ��ͼƬ��Դ·��
    //��Ҭ��
    _resourceMap["cauliflower"] = {
        "../Resources/Crops/Cauliflower/cauliflower_0.png",
        "../Resources/Crops/Cauliflower/cauliflower_1.png",
        "../Resources/Crops/Cauliflower/cauliflower_2.png",
        "../Resources/Crops/Cauliflower/cauliflower_3.png",
         "../Resources/Crops/Cauliflower/cauliflower_4.png"
    };

    //������
    _resourceMap["kale"] = {
       "../Resources/Crops/Kale/kale_0.png",
       "../Resources/Crops/Kale/kale_1.png",
       "../Resources/Crops/Kale/kale_2.png",
       "../Resources/Crops/Kale/kale_3.png",
       "../Resources/Crops/Kale/kale_4.png"
    };

    //�Ϲ�
    _resourceMap["pumpkin"] = {
   "../Resources/Crops/Pumpkin/pumpkin_0.png",
    "../Resources/Crops/Pumpkin/pumpkin_1.png",
    "../Resources/Crops/Pumpkin/pumpkin_2.png",
    "../Resources/Crops/Pumpkin/pumpkin_3.png",
    "../Resources/Crops/Pumpkin/pumpkin_4.png",
    "../Resources/Crops/Pumpkin/pumpkin_5.png"
    };
    //����
    _resourceMap["oak"] = {
   "../Resources/Crops/Oak/oak_0.png",
    "../Resources/Crops/Oak/oak_1.png",
    "../Resources/Crops/Oak/oak_2.png",
    "../Resources/Crops/Oak/oak_3.png"
    };

    //����
    _resourceMap["maple"] = {
   "../Resources/Crops/Maple/maple_0.png",
    "../Resources/Crops/Maple/maple_1.png",
    "../Resources/Crops/Maple/maple_2.png",
    "../Resources/Crops/Maple/maple_3.png"
    };

    //����
    _resourceMap["pine"] = {
   "../Resources/Crops/Pine/pine_0.png",
    "../Resources/Crops/Pine/pine_1.png",
    "../Resources/Crops/Pine/pine_2.png",
    "../Resources/Crops/Pine/pine_3.png"
    };

    //��ͨ��
    _resourceMap["grass"] = {
        "../Resources/Crops/grass.png"
    };

    //ʯͷ
    _resourceMap["stone"] = {
        "../Resources/Crops/stone.png"
    };
    //��2
    _resourceMap["grass_2"] = {
        "../Resources/Crops/grass_2.png"
    };

    //��ή
    _resourceMap["wilt"] = {
       "../Resources/Crops/wilt/wilt_0.png"
    };
    for (const auto& entry : _resourceMap) {
        CCLOG("Type: %s", entry.first.c_str());
        for (const auto& texture : entry.second) {
            CCLOG(" - Texture: %s", texture.c_str());
        }
    }

}

// ũ������������ڱ�����ͬ���ڲ�ͬ���ڣ�
std::unordered_map<std::string, std::unordered_map<Season, float>> Crops::_growthCycles = {
    {"cauliflower", {{Season::Spring, 50.0f}, {Season::Summer, 50.0f}, {Season::Fall, 60.0f}, {Season::Winter,72.0f}}},
    {"kale", {{Season::Spring, 30.0f}, {Season::Summer, 30.0f}, {Season::Fall, 40.0f}, {Season::Winter, 50.0f}}},
    {"pumpkin", {{Season::Spring, 50.0f}, {Season::Summer, 50.0f}, {Season::Fall, 60.0f}, {Season::Winter, 72.0f}}},
    {"oak", {{Season::Spring,50.0f}, {Season::Summer, 72.0f}, {Season::Fall, 96.0f}, {Season::Winter, 120.0f}}},
    {"maple", {{Season::Spring, 72.0f}, {Season::Summer, 72.0f}, {Season::Fall, 96.0f}, {Season::Winter, 120.0f}}},
    {"pine", {{Season::Spring, 72.0f}, {Season::Summer, 72.0f}, {Season::Fall, 96.0f}, {Season::Winter, 120.0f}}}

};

// ������׶�ͼƬ����ͬ���ڵ���ͼ��
std::unordered_map<std::string, std::unordered_map<Season, std::string>> Crops::_matureTextures = {
    {"oak", {{Season::Spring, "../Resources/Crops/Oak/oak_spring.png"},
                     {Season::Summer, "../Resources/Crops/Oak/oak_summer.png"},
                     {Season::Fall, "../Resources/Crops/Oak/oak_fall.png"},
                     {Season::Winter, "../Resources/Crops/Oak/oak_winter.png"}}
    },
    {"maple", {{Season::Spring, "../Resources/Crops/Maple/maple_spring.png"},
              {Season::Summer, "../Resources/Crops/Maple/maple_summer.png"},
              {Season::Fall, "../Resources/Crops/Maple/maple_fall.png"},
              {Season::Winter, "../Resources/Crops/Maple/maple_winter.png"}}
    },
    {"pine", {{Season::Spring, "../Resources/Crops/Pine/pine_spring.png"},
                 {Season::Summer, "../Resources/Crops/Pine/pine_spring.png"},
                 {Season::Fall, "../Resources/Crops/Pine/pine_fall.png"},
                 {Season::Winter, "../Resources/Crops/Pine/pine_winter.png"}}
    },
    {"cauliflower", {{Season::Spring, "../Resources/Crops/Cauliflower/cauliflower_4.png"},
                 {Season::Summer, "../Resources/Crops/Cauliflower/cauliflower_4.png"},
                 {Season::Fall, "../Resources/Crops/Cauliflower/cauliflower_4.png"},
                 {Season::Winter, "../Resources/Crops/Cauliflower/cauliflower_4.png"}}
    },
    {"kale", {{Season::Spring, "../Resources/Crops/Kale/kale_4.png"},
                 {Season::Summer, "../Resources/Crops/Kale/kale_4.png"},
                 {Season::Fall, "../Resources/Crops/Kale/kale_4.png"},
                 {Season::Winter, "../Resources/Crops/Kale/kale_4.png"}}
    },

     {"pumpkin", {{Season::Spring, "../Resources/Crops/Pumpkin/pumpkin_5.png"},
           {Season::Summer, "../Resources/Crops/Pumpkin/pumpkin_5.png"},
           {Season::Fall, "../Resources/Crops/Pumpkin/pumpkin_5.png"},
           {Season::Winter, "../Resources/Crops/Pumpkin/pumpkin_5.png"}}
     }
};

Crops::~Crops() {
    if (_state) {
        delete _state;
        _state = nullptr;
    }
}

CropData Crops::getCropData() {
    _cropData.Harvest = _type;
    _cropData.type = _type;
    if (this->isReadyToHarvest()==true) {
        _cropData.isHarvest=true;
    }
    else {
        _cropData.isHarvest = false;
    }
    _cropData.isWatered = _isWatered;
    _cropData.daysWithoutWater = _daysWithoutWater;
    _cropData.growthStage = _growthStage;
    _cropData.hasPests = _hasPests;
    _cropData.isFertilized = _isFertilized;
    return _cropData;
}

//���õ�ǰ������ȼ�
void Crops::setPlayerLevel(int level) {
    _playerLevel = level;
    CCLOG("Player level set to: %d", _playerLevel);
}

//������ȼ��ж��Ƿ�����ֲ����ũ����
bool Crops::canBePlanted(const std::string& cropType){
    if (cropType == "pumpkin" && _playerLevel < 3) {
        CCLOG("Error: Player level too low to plant pumpkin! Required level: 3");
        return false;
    }
    return true;
}


Crops* Crops::create(const std::string& type, int maxGrowthStage) {

    // �ڴ���֮ǰ�ȼ���ܷ���ֲ
    if (!canBePlanted(type)) {
        CCLOG("Cannot plant this crop due to insufficient player level.");
        return nullptr;
    }
    CCLOG("Creating Crop instance...");
    Crops* ret = new Crops();
    if (ret && ret->init(type, maxGrowthStage)) {
        ret->autorelease();
        CCLOG("Crop instance created successfully");
        return ret;
    }
    CC_SAFE_DELETE(ret);
    CCLOG("Crop instance creation failed");
    return nullptr;
}

// ʩ�ʺ������ı�isFertilizedΪtrue�����������ٶ�
void Crops::fertilize() {
    _isFertilized = true;
}

//��ʼ��ũ������Ϣ
bool Crops::init(const std::string& type, int maxGrowthStage) {
    CCLOG("Initializing Crop...");
    if (!Node::init()) {
        CCLOG("Error: Node::init failed");
        return false;
    }

    // ��ʼ����Դ�������״ε���ʱ��ִ�У�
    initializeResourceMap();

    this->_type = type;
    this->_growthStage = 0;
    this->_maxGrowthStage = maxGrowthStage;
    this->_growthTimer = 0.0f;
    this->_isWatered = false;
    this->_daysWithoutWater = 0;
    this->_isFertilized = 0;
    this->_hasPests = false;    // ��ʼ�޲��溦
    this->_pestProbability = 0.05f; // ��Ⱦ���� 5%
    // ��ʼ��ũ����ľ���
    _sprite = Sprite::create(_resourceMap[type][0]);
    if (_sprite == nullptr) {
        CCLOG("Error: Failed to load sprite for type: %s", type.c_str());
        return false;
    }

    _sprite->setScale(CROP_START_RATIO);
    // ����ê�㣨�������õ��ײ����ĵ㣩
    if (_type == "maple" || _type == "pine" || _type == "oak") {
        _sprite->setAnchorPoint(Vec2(CROP_HORIZONTAL_ANCHORPOINT, TREE_VERTICAL_ANCHORPOINT));
    }
    else {
        _sprite->setAnchorPoint(Vec2(CROP_HORIZONTAL_ANCHORPOINT, CROP_VERTICAL_ANCHORPOINT));
    }

    this->addChild(_sprite);

    // 初始化状态对象
    updateStateByGrowthStage();

    CCLOG("Crop initialized successfully");
    this->schedule([this](float dt) {
        this->updateGrowth(dt);
        }, 24.0f, "crop_update");
    return true;
}

// �������������ɺ�������ж��Ƿ���Ҫ��ˮ
void Crops::manageDrought(Weather currentWeather) {
    // ����Ƿ��ή
    if (!_isWatered) {
        _daysWithoutWater++;
        // ֻ�����ɺ������죬���첻��Ҫ��ˮ
        if (currentWeather == Weather::Dry) {
            // �ɺ�������ÿ���콽һ��ˮ
            if (_daysWithoutWater >= 2) {
                if (_resourceMap.find("wilt") != _resourceMap.end()) {
                    const auto& textures = _resourceMap["wilt"];
                    if (!textures.empty()) {
                        _sprite->setTexture(textures[0]);
                    }
                }
            }
        }
        else if (currentWeather == Weather::Sunny) {
            if (_daysWithoutWater >= 3) {
                if (_resourceMap.find("wilt") != _resourceMap.end()) {
                    const auto& textures = _resourceMap["wilt"];
                    if (!textures.empty()) {
                        _sprite->setTexture(textures[0]);
                    }
                }
            }
        }
        else if (currentWeather == Weather::Rainy) {
            _daysWithoutWater = 0;
        }
        // ��������죬�����κβ���
    }
    else {
        _daysWithoutWater = 0;
    }
}



//����ֲ�������״̬
void Crops::updateGrowth(float deltaTime) {

    const TimeManager* timeManager = TimeManager::getInstance();
    Season currentSeason = timeManager->getCurrentSeason();
    Crops::setSeason(currentSeason); // ���õ�ǰ����

    // ����Ƿ񱻲�ժ
    if (_isRemoved == true) {
        return;
    }
    // ��ȡ��ǰ���ڵ���������
    float growthSpeed = 5.0f;
    if (_growthCycles.find(_type) != _growthCycles.end()) {
        if (_growthCycles[_type].find(_currentSeason) != _growthCycles[_type].end()) {
            growthSpeed = _growthCycles[_type][_currentSeason];
        }
    }

    // ���ʩ�ʣ���������
    if (_isFertilized) {
        growthSpeed *= FERTILIZER_GROWTH_RATE; // ������������ 20%
    }

    // �ۻ�ʱ�䣬������һ�������׶�
    _growthTimer += deltaTime;
    if (_growthTimer >= growthSpeed && !_hasPests) {
        _growthTimer = 0.0f;
        _growthStage = std::min(_growthStage + 1, _maxGrowthStage);
        // 按新的生长阶段更新状态对象
        updateStateByGrowthStage();

        // ����ﵽ����׶Σ����ؼ��ڶ�Ӧ�ĳ���ͼƬ
        if (_growthStage == _maxGrowthStage) {
            if (_matureTextures.find(_type) != _matureTextures.end()) {
                auto seasonTexture = _matureTextures[_type][_currentSeason];
                _sprite->setTexture(seasonTexture);
                if (this->_type == "maple" || this->_type == "oak" || this->_type == "pine") {
                    _sprite->setScale(CROP_MATURE_RATIO);
                }
                CCLOG("Crop %s matured with texture: %s", _type.c_str(), seasonTexture.c_str());
                this->unschedule("crop_update");
            }
        }
        else {
            // ���������׶ε���ͼ����
            if (_resourceMap.find(_type) != _resourceMap.end()) {
                const auto& textures = _resourceMap[_type];
                if (_growthStage >= 0 && _growthStage < textures.size()) {
                    _sprite->setTexture(textures[_growthStage]);
                }
            }
        }
    }
    if (_type != "oak" && _type != "maple" && _type != "pine") {
        Weather currentWeather = Weather::Dry;
        currentWeather=timeManager->getCurrentWeather();
        this->manageDrought(currentWeather);
        checkPests(); // ÿ�θ���ʱ��鲡�溦
        _isWatered = false; // ÿ�θ��º����ý�ˮ״̬
    }

    // ����ήʱ��
    if (_daysWithoutWater > 0) {
        _wiltTime += deltaTime;
        if (_wiltTime >= WILTTIME) {  // ��ή����4��
            removeCrop();
            return;
        }
    }
    else {
        // ���δ��ή�����ÿ�ή��ʱ
        _wiltTime = 0.0f;
    }

}
void Crops::removeCrop() {
    if (this->_isRemoved) {
        CCLOG("Crop '%s' is already removed!", _type.c_str());
        return;
    }

    CCLOG("Crop '%s' is removed due to prolonged wilting!", _type.c_str());
    this->unschedule("crop_update");  // ֹͣ����
    if (this->getParent()) {
        this->removeFromParent();
    }
    this->_isRemoved = true;
}

// 根据当前生长阶段更新状态对象（State 模式核心入口）
void Crops::updateStateByGrowthStage() {
    // 已被移除的不再更新状态
    if (_isRemoved) return;

    // 清理旧状态
    if (_state) {
        delete _state;
        _state = nullptr;
    }

    // 根据生长阶段选择状态
    if (_growthStage <= 0) {
        _state = new SeedState();
    }
    else if (_growthStage == 1 && _maxGrowthStage >= 3) {
        // 初始发芽阶段
        _state = new SproutingState();
    }
    else if (_growthStage < _maxGrowthStage) {
        _state = new GrowingState();
    }
    else {
        _state = new MatureState();
    }
}

// 设置当前状态对象（供状态类或外部扩展调用）
void Crops::setState(CropState* state) {
    if (_state == state) return;
    if (_state) {
        delete _state;
    }
    _state = state;
}
//���µ�ǰ�ļ���
void Crops::setSeason(Season season) {
    if (_currentSeason != season) { // �����ظ�����
        _currentSeason = season;
        CCLOG("Season changed to %d", static_cast<int>(season));
    }
}

//��ȡ��ǰ�ļ���
Season Crops::getSeason() {
    return _currentSeason;
}

//���ֲ���Ƿ��в��溦
void Crops::checkPests() {
    if (_isRemoved == true) {
        return;
    }
    if (!_hasPests && CCRANDOM_0_1() < _pestProbability) { // ������ʸ�Ⱦ���溦
        _hasPests = true;
        CCLOG("Crop infected with pests!");

        // ������ͼ��ʾ���溦״̬���������ض�ͼƬ��
        _sprite->setTexture("../Resources/Crops/pests.png");
       
    }
}

//�������溦������ʹֲ��ָ�����
void Crops::treatPests() {
    // ��鵱ǰָ���Ƿ�Ϊ��ָ�룬��ֹ�������ͷŵĶ���
    if (_isRemoved == true) {
        return;
    }

    // ��� sprite �Ƿ�Ϊ��ָ��
    if (_sprite == nullptr) {
        CCLOG("Error: Attempt to update crop with null sprite.");
        return;
    }
    if (_hasPests) {
        _hasPests = false;
        CCLOG("Pests removed from crop!");

        // �ж��Ƿ��ڳ���׶Σ����һ�������׶Σ�
        if (_growthStage == _maxGrowthStage) {
            // �ӳ�����ͼӳ���л�ȡ��ǰ���ڵ���ͼ
            if (_matureTextures.find(_type) != _matureTextures.end()) {
                auto seasonTexture = _matureTextures[_type][_currentSeason];
                if (this->_type == "maple" || this->_type == "oak" || this->_type == "pine") {
                    _sprite->setScale(CROP_MATURE_RATIO);
                }
                _sprite->setTexture(seasonTexture);
                CCLOG("Restored crop to mature state with texture: %s", seasonTexture.c_str());
            }
        }
        else {
            // ���δ���죬�ָ�����Ӧ�����׶ε�������ͼ
            if (_resourceMap.find(_type) != _resourceMap.end()) {
                const auto& textures = _resourceMap[_type];
                if (_growthStage >= 0 && _growthStage < textures.size()) {
                    _sprite->setTexture(textures[_growthStage]);

                }
            }
        }
    }
}

//��ˮ�����Լ�ֲ�ｽˮ״̬�ĸ���
void Crops::waterCrop() {
    _isWatered = true;
    _daysWithoutWater = 0; // ��ˮ������δ��ˮ����
    // ����һ������������֡ͼƬ���
    Vector<SpriteFrame*> frames;

    frames.pushBack(SpriteFrame::create("../Resources/Animations/water/water_1.png", Rect(0, 0, 70, 70)));  // ����ÿ��ͼƬ�Ĵ�С�� 100x100
    frames.pushBack(SpriteFrame::create("../Resources/Animations/water/water_2.png", Rect(0, 0, 70, 70)));
    frames.pushBack(SpriteFrame::create("../Resources/Animations/water/water_3.png", Rect(0, 0, 70, 70)));
    frames.pushBack(SpriteFrame::create("../Resources/Animations/water/water_4.png", Rect(0, 0, 70, 70)));
    frames.pushBack(SpriteFrame::create("../Resources/Animations/water/water_5.png", Rect(0, 0, 70, 70)));

    // ��������
    Animation* animation = Animation::createWithSpriteFrames(frames, 0.2f);  // ÿ֡����0.2��
    Animate* animate = Animate::create(animation);

    // ��ʾ��ˮ����
    auto waterEffect = Sprite::create("../Resources/Animations/water/water_1.png");
    double x = _sprite->getPosition().x;
    double y = _sprite->getPosition().y;
    waterEffect->setPosition(Vec2(x, y - 8));
    waterEffect->setScale(WATER_RATIO);
    this->addChild(waterEffect, -1);

    // ִ�ж���
    waterEffect->runAction(animate);

    // �����������Ƴ�Ч��
    auto fadeOut = FadeOut::create(1.0f);
    auto removeEffect = CallFunc::create([waterEffect]() {
        waterEffect->removeFromParent();
        });

    auto sequence = Sequence::create(animate, fadeOut, removeEffect, nullptr);
    waterEffect->runAction(sequence);
}

//�ж�ũ�����Ƿ��Ѿ�����
bool Crops::isReadyToHarvest() const {
    // ���ũ�����Ƿ��Ѿ�����ժ
    if (_isRemoved == true) {
        return false;
    }

    // ��� sprite �Ƿ�Ϊ��ָ��
    if (_sprite == nullptr) {
        CCLOG("Error: Attempt to update crop with null sprite.");
        return false;
    }

    // 优先使用状态对象进行判断（State 模式）
    if (_state) {
        return _state->canHarvest(this);
    }

    // 兜底：保持原有逻辑
    return _growthStage >= _maxGrowthStage;
}

//����ũ���ﵱǰ�ĳɳ��׶�
void Crops::setGrowthStage(int stage) {
    // ��鵱ǰָ���Ƿ�Ϊ��ָ�룬��ֹ�������ͷŵĶ���
    if (_isRemoved == true) {
        return;
    }

    // ��� sprite �Ƿ�Ϊ��ָ��
    if (_sprite == nullptr) {
        CCLOG("Error: Attempt to update crop with null sprite.");
        return;
    }
    _growthStage = std::min(stage, _maxGrowthStage); // ȷ���׶β��������ֵ

    // 生长阶段被外部修改时，同步更新状态对象
    updateStateByGrowthStage();
    // �����Դӳ������Ƿ��е�ǰũ�������͵���Դ
    if (_growthStage == _maxGrowthStage) {
        // ����ǳ���׶Σ����س���׶ζ�Ӧ�ļ�����ͼ
        if (_matureTextures.find(_type) != _matureTextures.end()) {
            auto it = _matureTextures[_type].find(_currentSeason);
            if (it != _matureTextures[_type].end()) {
                if (this->_type == "maple" || this->_type == "oak" || this->_type == "pine") {
                    _sprite->setScale(CROP_MATURE_RATIO);
                }
                _sprite->setTexture(it->second);
                CCLOG("Set crop '%s' to mature state with texture: %s", _type.c_str(), it->second.c_str());
            }
        }
    }
    else if (_resourceMap.find(_type) != _resourceMap.end()) {
        const auto& textures = _resourceMap[_type];
        if (_growthStage >= 0 && _growthStage < textures.size()) {
            _sprite->setTexture(textures[_growthStage]);
        }
    }
}

//ũ�����ջ�ʱ���ú�����ɾ����ǰũ���ﾫ��
void Crops::harvestCrop() {
    // ��鵱ǰָ���Ƿ�Ϊ��ָ�룬��ֹ�������ͷŵĶ���
    if (this == nullptr) {
        CCLOG("Error: Attempt to update a null crop pointer.");
        return;
    }
    if (_isRemoved == true) {//�Ѿ�����ժ�˵Ĳ����ظ���ժ
        return;
    }
    //if (!canBePlanted()) { // �����������������Ҫ�ǵȼ���飩
    //    CCLOG("Crop '%s' cannot be planted due to level restriction.", _type.c_str());
    //    return;
    //}

    if (isReadyToHarvest()) {
        removeCrop();
    }
    else {
        CCLOG("Crop '%s' is not ready for harvest!", _type.c_str());
    }
}

//������������
void Crops::chopTree() {
    CCLOG("Tree '%s' is swaying...", _type.c_str());

    // ����Ƿ�Ϊ������
    if (_type != "oak" && _type != "maple" && _type != "pine") {
        CCLOG("Error: Crop '%s' is not a tree and cannot swing.", _type.c_str());
        return;
    }

    // ������ҡ�ڵķ��Ⱥ��ٶ�
    float moveDistance = 3.0f; // ˮƽ�ƶ��ľ��루���أ�
    float swingAngle = 3.0f;    // ҡ�ڵĽǶȣ��ȣ�
    float duration = 0.5f;      // ����ҡ������ʱ�䣨�룩
    int repeatCount = 3;        // ҡ�ڴ���

    // ��������ҡ�ڵĶ���
    auto moveLeft = MoveBy::create(duration, Vec2(-moveDistance, 0)); // ����
    auto rotateLeft = RotateBy::create(duration, -swingAngle);        // ����ת

    // ��������ҡ�ڵĶ���
    auto moveRight = MoveBy::create(duration, Vec2(moveDistance, 0)); // ����
    auto rotateRight = RotateBy::create(duration, swingAngle);        // ����ת

    // �ϳ�ҡ�ڶ���
    auto swingLeft = Spawn::create(moveLeft, rotateLeft, nullptr);
    auto swingRight = Spawn::create(moveRight, rotateRight, nullptr);
    auto swingSequence = Sequence::create(swingLeft, swingRight, nullptr);

    // ҡ�ڶ����ظ�ָ������
    auto repeatSwing = Repeat::create(swingSequence, repeatCount);

    // ����������ת 90 �ȶ���
    auto rotateFinal = RotateBy::create(0.5f, -90.0f); // 0.5 ��������ת 90 ��

    // ���ӵ�����ʧ����
    auto fadeOut = FadeOut::create(1.0f); // 1 �뵭��

    // �Ƴ��ڵ�Ļص�
    auto removeTree = CallFunc::create([this]() {
        CCLOG("Tree '%s' has disappeared after swaying and rotating.", _type.c_str());
        this->removeFromParentAndCleanup(true);
        });

    // ������ж�����ҡ�� -> ��ת -> ���� -> �Ƴ�
    auto fullSequence = Sequence::create(repeatSwing, rotateFinal, fadeOut, removeTree, nullptr);

    // ִ�ж���
    this->_sprite->runAction(fullSequence);
}


