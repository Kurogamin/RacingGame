// Copyright 2023 Teyon. All Rights Reserved.

#include "RacingGameInstance.h"

URacingGameInstance::URacingGameInstance() {
	CarPartsColors.Init(FLinearColor::Black, 4);
	CustomParts.Init(false, 4);
}

int URacingGameInstance::GetNumberOfLaps() const {
	return NumberOfLaps;
}

int URacingGameInstance::GetNumberOfSeconds() const {
	return NumberOfSeconds;
}

LapData URacingGameInstance::GetBestLap() const {
	return BestLapData;
}

RaceType URacingGameInstance::GetCurrentRaceType() const {
	return CurrentRaceType;
}

void URacingGameInstance::SetNumberOfLaps(int NewNumberOfLaps) {
	NumberOfLaps = NewNumberOfLaps;

	if (NumberOfLaps == 1) {
		CurrentRaceType = RaceType::Time;
	} else {
		CurrentRaceType = RaceType::Laps;
	}
}

void URacingGameInstance::SetNumberOfSeconds(int NewNumberOfSeconds) {
	NumberOfSeconds = NewNumberOfSeconds;
}

void URacingGameInstance::SetBestLap(LapData NewBestLap) {
	BestLapData = NewBestLap;
}

void URacingGameInstance::SetCustomMaterialColor(int PartIndex, FLinearColor Color) {
	CarPartsColors[PartIndex] = Color;
}

void URacingGameInstance::SetCustomPart(int PartIndex, bool IsCustom) {
	CustomParts[PartIndex] = IsCustom;
}

void URacingGameInstance::SetCustomParts(TArray<bool> NewCustomParts) {
	CustomParts = NewCustomParts;
}

TArray<FLinearColor> URacingGameInstance::GetCustomMaterialColors() {
	return CarPartsColors;
}

TArray<bool> URacingGameInstance::GetCustomParts() {
	return CustomParts;
}
