// Copyright 2023 Teyon. All Rights Reserved.

#pragma once

#include "../Gameplay/LapData.h"
#include "CoreMinimal.h"
#include "Engine/GameInstance.h"

#include "RacingGameInstance.generated.h"

/**
 *
 */
UCLASS()
class PRAKTYKI_API URacingGameInstance : public UGameInstance {
	GENERATED_BODY()
private:
	int NumberOfLaps;
	int NumberOfSeconds;
	RaceType CurrentRaceType;

public:
	URacingGameInstance();

	int GetNumberOfLaps() const;
	int GetNumberOfSeconds() const;
	RaceType GetCurrentRaceType() const;

	void SetNumberOfLaps(int NewNumberOfLaps);
	void SetNumberOfSeconds(int NewNumberOfSeconds);
};
