// Copyright 2023 Teyon. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"

/**
 *
 */
enum PRAKTYKI_API RaceType { Time, Laps };

struct PRAKTYKI_API LapData {
public:
	static FString FloatToRoundedString(float Value, int Precision = 3);

	float LapTime;
	float LapTimeLost;
	TArray<float> CheckpointTimes;

	LapData();
	LapData(float LapTime, float LapTimeLost);

	FString ToRichString() const;
	bool operator>(const LapData &other) const;
};
