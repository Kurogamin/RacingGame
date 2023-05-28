// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../Gameplay/LapData.h"
#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include <set>

#include "PraktykiGameModeBase.generated.h"

class AGameHUD;
enum RaceType;

/**
 *
 */
UCLASS()
class PRAKTYKI_API ARaceGameModeBase : public AGameModeBase {
	GENERATED_BODY()
private:
	AGameHUD *GameHUD = nullptr;

	int NumberOfLaps;
	int NumberOfSeconds;
	RaceType CurrentRaceType;
	float GameStartTime;
	FTimerHandle EndGameTimer;

	// Checkpoints
	int NumberOfCheckpoints = 0;

	TSet<int> CheckpointsReached;
	bool CanFinishLap = false;

	// Laps
	int CurrentLap = 0;
	float LapStartTime;
	float CurrentLapTime;

	// Time Lost
	float CurrentLapTimeLost = 0.0f;

	// Lap Times
	TArray<LapData> LapTimes;
	LapData BestLapData;

	void AddLapData();

protected:
	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;

public:
	ARaceGameModeBase();

	void AddTimeLost(float AddValue);
	void AddCheckpoint(int CheckpointNumber);
	void FinishLap();
	void EndCurrentRace();
	int GetNumberOfLaps();
	int GetNumberOfCheckpoints();
	bool GetCanFinishLap();
};
