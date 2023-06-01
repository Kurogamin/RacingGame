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
	LapData BestLapData;
	RaceType CurrentRaceType;

	TArray<FLinearColor> CarPartsColors;
	TArray<bool> CustomParts;

public:
	URacingGameInstance();

	int GetNumberOfLaps() const;
	int GetNumberOfSeconds() const;
	LapData GetBestLap() const;
	RaceType GetCurrentRaceType() const;

	void SetNumberOfLaps(int NewNumberOfLaps);
	void SetNumberOfSeconds(int NewNumberOfSeconds);
	void SetBestLap(LapData NewBestLap);
	void SetCustomMaterialColor(int PartIndex, FLinearColor Color);
	void SetCustomPart(int PartIndex, bool IsCustom);
	void SetCustomParts(TArray<bool> NewCustomParts);
	TArray<FLinearColor> GetCustomMaterialColors();
	TArray<bool> GetCustomParts();
};
