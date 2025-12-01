/****************************************************************
 * Project Name:  Stardew_Valley
 * File Name:     AnimalBuilder.h
 * File Function: Animal 构建器，负责按配置创建并初始化 Animal 实例
 * Author:        设计模式重构
 * Update Date:   2024/12/17
 * License:       MIT License
 ****************************************************************/
#ifndef ANIMAL_BUILDER_H
#define ANIMAL_BUILDER_H

#include "cocos2d.h"
#include <string>
#include "Animal.h"

USING_NS_CC;

/**
 * Builder 模式：
 *  - 通过链式配置（type / position 等）构建 Animal
 *  - 内部依然复用现有的 Animal::create 接口，保证向后兼容
 */
class AnimalBuilder {
public:
    AnimalBuilder& withType(const std::string& type);
    AnimalBuilder& withStartPosition(const Vec2& position);

    /**
     * 构建并返回 Animal 实例
     * 目前仅使用 type + startPosition，后续如需扩展更多配置，
     * 可以在此处集中处理，而不影响外部调用者。
     */
    Animal* build() const;

private:
    std::string _type{"chicken"};
    Vec2 _startPosition{Vec2::ZERO};
};

#endif // ANIMAL_BUILDER_H


