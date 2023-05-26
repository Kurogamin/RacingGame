// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../UI/GameHUD.h"
#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include <set>

#include "PraktykiGameModeBase.generated.h"

/**
 *
 */
UCLASS()
class PRAKTYKI_API ARaceGameModeBase : public AGameModeBase {
	GENERATED_BODY()
private:
	AGameHUD *GameHUD = nullptr;

	// Checkpoints
	int NumberOfCheckpoints = 0;

	std::set<int> CheckpointsReached;
	bool CanFinishLap = false;

	// Laps
	int CurrentLap = 0;
	float LapStartTime;

	UPROPERTY(EditAnywhere)
	int NumberOfLaps = 0;

	// Time Lost
	float TimeLost = 0.0f;

protected:
	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;

public:
	ARaceGameModeBase();

	void AddTimeLost(float AddValue);
	void AddCheckpoint(int CheckpointNumber);
	void FinishLap();
	int GetNumberOfLaps();
	int GetNumberOfCheckpoints();
	bool GetCanFinishLap();
};
