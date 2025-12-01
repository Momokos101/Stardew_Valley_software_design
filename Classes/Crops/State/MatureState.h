/****************************************************************
 * Project Name:  Stardew_Valley
 * File Name:     MatureState.h
 * File Function: 成熟状态
 * Author:        AI-Assistant
 * Update Date:   2024/12/22
 * License:       MIT License
 ****************************************************************/
#pragma once
#ifndef __MATURE_STATE_H__
#define __MATURE_STATE_H__

#include "Crops/State/CropState.h"

class MatureState : public CropState {
public:
    bool canHarvest(const Crops* /*crop*/) const override {
        return true;
    }
};

#endif // !__MATURE_STATE_H__


