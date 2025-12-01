/****************************************************************
 * Project Name:  Stardew_Valley
 * File Name:     GrowingState.h
 * File Function: 生长状态
 * Author:        AI-Assistant
 * Update Date:   2024/12/22
 * License:       MIT License
 ****************************************************************/
#pragma once
#ifndef __GROWING_STATE_H__
#define __GROWING_STATE_H__

#include "Crops/State/CropState.h"

class GrowingState : public CropState {
public:
    bool canHarvest(const Crops* /*crop*/) const override {
        return false;
    }
};

#endif // !__GROWING_STATE_H__


