// Copyright 2023 Teyon. All Rights Reserved.

#include "RacingGameInstance.h"

URacingGameInstance::URacingGameInstance() {
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
