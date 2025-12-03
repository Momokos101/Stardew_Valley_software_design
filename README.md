# Stardew_Valley

星露谷物语[Sprit-Sheet-Resource](https://www.spriters-resource.com/pc_computer/stardewvalley/)

## 项目名称

Stardew_Valley（软件设计模式重构版）

## 项目简介

A project of Stardew Valley based on [Cocos2d-x 3.17.2](https://docs.cocos.com/cocos2d-x/manual).

基于 [Cocos2d-x 3.17.2](https://docs.cocos.com/cocos2d-x/manual) 开发的星露谷游戏项目。

> * Programing Paradigm 2024 (2024年同济大学程序设计范式)

该项目是一个基于 Cocos2d-x 的《星露谷物语》仿制游戏，灵感来自于《星露谷》《我的世界》等游戏，玩家将管理自己的农场，种植作物，养殖动物，与镇上的居民互动，参与节日活动，并探索周围的自然环境。

### 软件设计模式版本说明

当前仓库为在原有游戏功能基础上的“**软件设计模式重构版本**”，在不改变主要玩法的前提下，对核心模块进行了系统性的面向对象重构，重点包括：

- **商店与定价系统：策略模式（Strategy）**
  - 抽象 `PricingStrategy` 接口，具体实现 `SeasonalPricingStrategy`（季节价格策略）、`WeatherPricingStrategy`（天气价格策略）、`AffectionPricingStrategy`（好感度价格策略预留），由 `Store` 统一调度。
- **时间系统：观察者模式（Observer）**
  - `TimeManager` 作为时间发布者，`Store`、作物等实现 `TimeObserver` 接口，响应日期、季节、时间变化。
- **农作物生长：状态模式（State）**
  - 通过 `CropState` 抽象接口及 `SeedState`、`SproutingState`、`GrowingState`、`MatureState` 等具体状态类，管理作物多阶段生长逻辑。
- **地图系统：桥接 + 适配器 + 工厂模式（Bridge / Adapter / Factory）**
  - 使用 `GameMap` + `MapImplementation` 解耦地图抽象与具体实现；
  - 使用 `MapAdapter` 给上层提供统一地图接口；
  - 使用 `MapFactory` 统一创建农场、小镇、矿洞、室内等不同地图实例。
- **NPC 管理：空对象模式（Null Object）**
  - 实现 `NullNPC` 类作为空对象，当 `NpcManager::getNPCByName()` 找不到指定 NPC 时返回 `NullNPC` 实例而非 `nullptr`；
  - 消除调用方的空指针检查，提升代码安全性与简洁性；
  - 参考：[Wikipedia - Null Object Pattern](https://en.wikipedia.org/wiki/Null_object_pattern)

更详细的设计模式说明与重构动机，见根目录文档：`设计模式重构报告.md`。

### 运行环境与运行方式

#### 运行环境

- **操作系统**：Windows 10 / Windows 11（32/64 位均可，推荐 64 位）；
- **开发工具**：Visual Studio 2022（Community 版及以上），已安装 **C++ 桌面开发** 工作负载；
- **图形库与引擎**：项目自带完整的 `cocos2d-x 3.17.2` 源码与依赖，无需单独安装引擎。

#### 运行步骤（本地编译运行）

1. **获取代码**
   - 使用 `git clone` 或 GitHub Desktop 将本仓库完整克隆到本地，例如：`E:\Stardew_Valley_软件设计`。
   - 保证 `cocos2d`、`Classes`、`proj.win32` 等目录结构完整。

2. **打开解决方案**
   - 启动 Visual Studio 2022；
   - 通过“**文件 → 打开 → 项目/解决方案**”，打开：  
     `proj.win32/Stardew_Valley.sln`。

3. **选择配置**
   - 在 VS 顶部工具栏中，将配置设置为：  
     - **方案配置**：`Debug`（或 `Release`）  
     - **方案平台**：`Win32`

4. **生成依赖库**
   - 解决方案中包含几个子项目：`librecast`、`libSpine`、`libcocos2d`、`Stardew_Valley`；
   - 推荐的顺序是：  
     1）右键 `librecast` → “生成”；  
     2）右键 `libSpine` → “生成”；  
     3）右键 `libcocos2d` → “生成”；  
     4）最后右键 `Stardew_Valley` → “生成”；  
   - 或者直接在解决方案上右键选择“**重新生成解决方案**”，VS 会自动按依赖关系构建。

5. **注意避免文件被占用**
   - 若之前运行过游戏，`proj.win32/Debug.win32/Stardew_Valley.exe` 可能仍在运行；
   - 在重新生成前，务必关闭游戏窗口，或在任务管理器中结束相关进程，否则会出现“**访问被拒绝 / 无法删除 EXE 或 DLL**”的错误。

6. **运行游戏**
   - 在 `Stardew_Valley` 项目上右键 → 选择“**设为启动项目**”；
   - 点击 VS 顶部的“**本地 Windows 调试器**”绿色三角按钮，即可启动游戏；
   - 或者在资源管理器中直接双击运行：  
     `proj.win32/Debug.win32/Stardew_Valley.exe`。

7. **资源路径说明**
   - 游戏运行时会从 `Resources` 目录加载图片、音效、字体、地图等资源；
   - 不要改变 `proj.win32` 与 `Resources` 的相对路径关系（否则需要同步修改 VS 中的资源拷贝脚本与搜索路径）。

---
## 项目组成

* `/Classes`
类定义与类实现

* `/Resources`
资源文件

* `/GameData`
游戏数据

* `/cocos2d`
依赖文件

* `/proj.win32`
游戏程序

## 项目实现功能与项目技术细节（设计模式重构版）

### 基础功能

* [X] 有初始界面
* [X] 支持背景音效
* [X] 支持耕种、种植、收获农作物等操作
* [X] 支持养殖动物并获取相关畜产品
* [X] 支持对游戏内物品资源的存储
* [X] 支持与小镇上的NPC居民建立关系
* [X] 支持接受居民委托的相关任务
* [X] 支持挖掘矿物，钓鱼和收集稀有物品
* [X] 支持技能升级以及随技能提升解锁新的物品

### 拓展功能
* [X] 支持存档功能
* [X] 支持合成物品
* [X] 天气系统
* [X] 商店系统

### 功能和架构

  * [x] 界面精美

    * 界面 UI 设计

      * 页面设计

        本项目根据场景切换一共设计了 4 个地图，分别为农场地图（FarmMap）、小镇地图（TownMap）、矿洞地图（MineMap）、室内地图（IndoorMap）。

      * 按钮设计

        Cocos2dx 一共给了两个状态的按钮，分别为标准态和激活态。但为了保证画面精美，本项目还设计了按钮的悬浮态，保证鼠标划过的时候按钮会进行一定比例的放大动画，在设计按钮时，本项目也考虑了与当前场景色调的一致性，使得画面和谐精美。

      * 属性与商店 UI 设计

        游戏的背包和商店等 UI 参考了原游戏，保证了游戏场景的和谐性。

    * 图标设计

      * 物品图标设计

        本游戏页面参考了《星露谷》，故物品的图标从官网截取，并根据画面的和谐，调整了大小与形状。

  * [x] 项目目录结构清晰

    本项目根据文件的不同功能，将外界资源和项目源文件进行了分类。所有类都被归置 `Classes` 文件夹，更能直观地管理各类文件；同时将各种资源文件都放置在 `Resources` 文件夹，包括所有图片资源以及音乐资源、字体资源， `proj.win32` 则用于存储解决方案以及程序入口等源文件。

  * [x] 尽可能多地使用了 C++11 特性

    * 类型推导

      C++11 引入了 `auto` 关键字，其允许编译器自动推导变量或表达式的类型，方便开发者编码也简化了代码。
      
      `auto` ：让编译器在编译器就推导出变量的类型，可以通过 `=` 右边的类型推导出变量的类型。

      本项目在复杂数据类型时使用了 `auto` 方便创建变量以面对复杂的类型表达式，同时减少由于类型错误造成的 bug，也提高了维护性。使用举例如下：

      ```cpp
          // 创建并切换到游戏主场景
          auto farmScene = GameMainScene::createScene();
          auto transition = TransitionFade::create(SCENE_TRANSITION_TIME, farmScene);
      ```

    * 构造函数参数列表初始化

      C++11 引入了列表初始化（也称为统一初始化），这是一种使用花括号 `{ }` 来初始化对象的新语法。它提供了一种更一致、更安全的初始化方式，并且能用于几乎所有类型的初始化，包括基本数据类型、对象、数组以及容器等。使用举例如下：

      ```cpp
        CharacterObjectList::CharacterObjectList() :
      	_maxObjectKindCount(OBJECT_LIST_ROWS*OBJECT_LIST_COLS),
	      _currentObjectIndex(0),
	      _openObjectList(false),
	      _openBox(false),
      	_openShop(false),
      	_openSynthesisTable(false),
      	_isEKeyEnabled(true),
      	_isRKeyEnabled(true),
      	_isTKeyEnabled(true),
      	_isYKeyEnabled(true),
	      _callback(nullptr)
      {

        if (!loadData("../GameData/CharacterObjectListData.dat")) {
          // 初始化物品栏
          _objectList.resize(_maxObjectKindCount, { ObjectListNode{ {None,nullptr}, 0 ,Unselected } });
          pickUpObject("BeginnerHoe", 1);
          pickUpObject("BeginnerAxe", 1);
          pickUpObject("BeginnerPickaxe", 1);
          pickUpObject("BeginnerFishingRods", 1);
          pickUpObject("BeginnerKattle", 1);
          pickUpObject("scythe", 1);
          pickUpObject("Timber", 5);
        }
        pickUpObject("Timber", 5);
      }

      ```

    * 基于范围的 `for` 循环

      C++11 引入了基于范围的 `for` 循环（Range-based for loop），这是一种新的循环语法，使得遍历容器（如数组、向量、列表等）和范围变得更加简单和直观。这种循环方式自动迭代容器或范围中的每个元素，无需手动管理迭代器或索引。使用举例如下：

      ```cpp
        // 创建可合成物品图片
        int index = 0;
        for (const auto& object : GAME_BASE_OBJECTS_ATTRS) {
            if (object._synthesis == true) {
                _synthesisObjectSpriteImage[index] = HoverMenuItemImage::create(object._fileName, object._fileName, [this, object](cocos2d::Ref* sender) {_character->synthesizeObject(object);}, OBJECT_NODE_SCALE);
                _synthesisObjectSpriteImage[index]->setPosition(LocationMap::getInstance().getSysthesisTableLocationMap().at(index));
                _synthesisObjectSpriteImage[index]->setScale(OBJECT_NODE_SCALE);
                this->addChild(_synthesisObjectSpriteImage[index], OBJECT_LAYER_GRADE);
                _synthesisObjectSpriteImage[index]->setVisible(false);
                index++;
            }
        }
      ```

    * 继承构造函数

      继承构造函数（Inheriting Constructors）是 C++11 标准中引入的一个特性，它允许派生类继承基类的构造函数。这个特性主要解决了在派生类中重复编写与基类构造函数相同的代码的问题，从而提高了代码的可维护性和简洁性。使用举例如下：

      ```cpp
      Character::Character():
          CharacterAction(),
          CharacterMove(){ }
      ```

    * 空指针关键字 `nullptr`

      C++11 引入了 `nullptr` 关键字，它是一个表示空指针的字面量，用于替代传统 C++ 中的 `NULL` 。在之前的 C++ 标准中， `NULL` 通常被定义为 `0` 或 `((void*)0)` ，这可能导致类型歧义和一些难以发现的错误。 `nullptr` 的引入解决了这些问题，同时提供了更清晰、更安全的方式来表示空指针。使用举例如下：

      * 初始化空指针

        ```cpp
        Character* _character = nullptr;    
        ```

      * 指针重置为“无对象”

        ```cpp
                ObjectImageInfo currentObjectImage;
                if (_startLocation.status == OpenedObjectList) {
                    currentObjectImage = _openedObjectSpriteImage[_startLocation.position];
                    _openedObjectSpriteImage[_startLocation.position] = { nullptr,nullptr };

                }
                else if (_startLocation.status == OpenedBoxList && _boxObjectListStatus == true && Box::getInstance().getBoxCount() != 0) {
                    currentObjectImage = _boxObjectSpriteImage[_startLocation.position];
                    _boxObjectSpriteImage[_startLocation.position] = { nullptr,nullptr };
                }
        ```

    * 修饰常量 `constexpr`

      `constexpr` 是 C++11 新引入的关键字，用于编译时的常量和常量函数。 `constexpr` 修饰的才是真正的常量，它会在编译期间就会被计算出来，整个运行过程中都不可以被改变， `constexpr` 可以用于修饰函数，这个函数的返回值会尽可能在编译期间被计算出来当作一个常量，但是如果编译期间此函数不能被计算出来，那它就会当作一个普通函数被处理。使用举例如下：

      ```h
      constexpr int DESIGN_RESOLUTION_WIDTH = 1920;                          
      constexpr int DESIGN_RESOLUTION_HEIGHT = 1080;                         
      ```

    * `lambda` 表达式

      `lambda` 表达式是 C++11 最重要也最常用的一个特性之一。它能够就地匿名定义目标函数或函数对象，不需要额外写一个命名函数或者函数对象。以更直接的方式去写程序，好的可读性和可维护性。使用示例如下：

      ```cpp
        this->schedule([this](float deltaTime) {
            if (_viewController) { _viewController->update(deltaTime); }
            const auto cameraPosition = Camera::getDefaultCamera()->getPosition();
            const auto visibleSize = Director::getInstance()->getVisibleSize();
            Vec2 cameraOffset = cameraPosition - Vec2(visibleSize.width / 2, visibleSize.height / 2);
            _uiContainer->setPosition(cameraOffset);  
            if (_uiLayer) { _uiLayer->update(deltaTime); }
            }, "ViewControllerUpdate");
      ```
    * 多态性

      在项目中，多态性是一个核心的面向对象编程特性，它使得不同类型的对象可以通过统一的接口进行操作。

      * 基类与派生类

 	项目中定义了一个基类 GameMap，该类提供了地图相关功能的接口和基础实现。具体的地图实现类（如 FarmMap、IndoorMap、MineMap 和 TownMap）则从 GameMap 继承而来。每个子类根据自身的需要重新实现基类中的虚函数。

      * 虚函数

        在派生类中，这些虚函数可以根据具体的地图类型重写，以实现特定的行为。这意味着你可以使用基类指针来操作子类对象，而程序会在运行时根据对象的实际类型决定调用哪个函数，使用示例如下：

    	```cpp
     	virtual void replaceTileAt(const std::string& layerName, const Vec2& tileCoord, int newGID, bool isUserAction);
    	virtual Node* getNodeAtPosition(const Vec2& tilePos);
        ```

      * 智能指针
        
	智能指针是 C++11 引入的一种用来管理动态分配内存的工具，它通过 RAII（资源获取即初始化）方式来自动管理对象的生命周期。下面将详细介绍智能指针的类型、特点以及在项目中的使用场景。

	* std::shared_ptr

     	  std::shared_ptr 是一种共享所有权的智能指针，可以有多个指针指向同一个对象，通过引用计数来管理对象的生命周期。只有当所有指向该对象的 std::shared_ptr 被销毁时，才会释放内存，使用示例如下：
    
	  ```
      	  std::shared_ptr<GameObject> targetObjectPtr = std::make_shared<GameToolObject>(targetObject);
          ```    

    * `Unicode` 编码支持

      C++11 引入了对 `Unicode` 的支持，并且引入了几种新的字符串字面量，在本项目中，使用了 `u8` 。 `u8` 用于表示 UTF-8 编码的字符串字面量。UTF-8 是一种可变长度的字符编码，用于编码 `Unicode` 字符。这使得 C++ 程序能够更容易地处理多种语言和字符集。使用举例如下：

      ```h
      const std::string APPLICATION_TITLE = u8"星露谷物语 Stardew Valley";    
      ```

  * [x] 动态市场系统

    玩家可以购买和出售商店随机刷新的商品，商品购买和出售的价格会受到日期和季节的影响，不同商品价格浮动的时期不同。

  * [x] 游戏还原度高

    本游戏以《星露谷》游戏为参考，对游戏场景界面、游戏玩法、游戏音乐音效以及游戏角色进行了设计参考。

    * 游戏场景界面按钮

      本项目场景均从《星露谷》官网寻找适合大小的背景图，以更贴合游戏原型。

    * 游戏背景音乐与音效

      游戏背景音乐结合了《星露谷》中的音乐音效，更加还原。

    * 游戏地图与交互动画

      游戏地图鱼交互动画按《星露谷》官方地图和动画制作，所有地图均能在官方地图找到对应。

  * [x] 常变量的集中定义

    本项目的 `Constant.h` 头文件集中存放了所有常变量的定义，注释完备，方便项目维护。

