/****************************************************************
 * Project Name:  Stardew_Valley
 * File Name:     AnimalBuilder.cpp
 * File Function: Animal 构建器实现
 * Author:        设计模式重构
 * Update Date:   2024/12/17
 * License:       MIT License
 ****************************************************************/

#include "AnimalBuilder.h"

AnimalBuilder& AnimalBuilder::withType(const std::string& type) {
    _type = type;
    return *this;
}

AnimalBuilder& AnimalBuilder::withStartPosition(const Vec2& position) {
    _startPosition = position;
    return *this;
}

Animal* AnimalBuilder::build() const {
    // 当前实现直接委托给现有的 Animal::create，保持接口向后兼容
    return Animal::create(_type, _startPosition);
}


