/****************************************************************
 * Project Name:  Stardew_Valley
 * File Name:     SproutingState.h
 * File Function: 发芽状态
 * Author:        AI-Assistant
 * Update Date:   2024/12/22
 * License:       MIT License
 ****************************************************************/
#pragma once
#ifndef __SPROUTING_STATE_H__
#define __SPROUTING_STATE_H__

#include "Crops/State/CropState.h"

class SproutingState : public CropState {
public:
    bool canHarvest(const Crops* /*crop*/) const override {
        return false;
    }
};

#endif // !__SPROUTING_STATE_H__


