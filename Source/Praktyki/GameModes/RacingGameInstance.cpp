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

void URacingGameInstance::SetNumberOfLaps(int NewNumberOfLaps) {
	NumberOfLaps = NewNumberOfLaps;
}

void URacingGameInstance::SetNumberOfSeconds(int NewNumberOfSeconds) {
	NumberOfSeconds = NewNumberOfSeconds;
}