// Copyright 2023 Teyon. All Rights Reserved.

#include "LapData.h"

FString LapData::FloatToRoundedString(float Value, int Precision) {
	if (Precision <= 0) {
		Precision = 1;
	}

	int Multiplier = FMath::Pow(10.0f, (float)Precision);
	float RoundedValue = FMath::RoundToZero(Value * Multiplier) / Multiplier;

	FString RoundedString = FString::Printf(TEXT("%.3f"), RoundedValue);

	return RoundedString;
}

LapData::LapData() {
	LapTime = 0.0f;
	LapTimeLost = 0.0f;
}

LapData::LapData(float LapTime, float LapTimeLost) {
	this->LapTime = LapTime;
	this->LapTimeLost = LapTimeLost;
}

LapData::LapData(float LapTime, float LapTimeLost, TArray<float> CheckpointTimes) {
	this->LapTime = LapTime;
	this->LapTimeLost = LapTimeLost;
	this->CheckpointTimes = CheckpointTimes;
}

FString LapData::ToRichString() const {
	FString LapTimeString = FloatToRoundedString(LapTime, 3);
	FString LapTimeLostString = FloatToRoundedString(LapTimeLost, 3);
	return FString::Printf(TEXT("LapTime: %s <Red>(+%s)</>s"), *LapTimeString, *LapTimeLostString);
}

bool LapData::operator>(const LapData &other) const {
	if (other.LapTime == 0.0f) {
		return true;
	}
	return LapTime + LapTimeLost < other.LapTime + other.LapTimeLost;
}
