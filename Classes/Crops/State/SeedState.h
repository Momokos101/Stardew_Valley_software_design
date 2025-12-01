/****************************************************************
 * Project Name:  Stardew_Valley
 * File Name:     SeedState.h
 * File Function: 种子状态
 * Author:        AI-Assistant
 * Update Date:   2024/12/22
 * License:       MIT License
 ****************************************************************/
#pragma once
#ifndef __SEED_STATE_H__
#define __SEED_STATE_H__

#include "Crops/State/CropState.h"

class SeedState : public CropState {
public:
    bool canHarvest(const Crops* /*crop*/) const override {
        return false;
    }
};

#endif // !__SEED_STATE_H__


