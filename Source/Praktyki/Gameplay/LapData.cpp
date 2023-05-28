// Copyright 2023 Teyon. All Rights Reserved.

#include "LapData.h"

LapData::LapData() {
	LapTime = 0.0f;
	LapTimeLost = 0.0f;
}

LapData::LapData(float LapTime, float LapTimeLost) {
	this->LapTime = LapTime;
	this->LapTimeLost = LapTimeLost;
}
