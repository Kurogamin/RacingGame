// Copyright 2023 Teyon. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"

/**
 *
 */
enum PRAKTYKI_API RaceType { Time, Laps };

struct PRAKTYKI_API LapData {
public:
	float LapTime;
	float LapTimeLost;
	LapData();
	LapData(float LapTime, float LapTimeLost);
};
