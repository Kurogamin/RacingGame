// Fill out your copyright notice in the Description page of Project Settings.

#include "PraktykiGameModeBase.h"
#include "../Gameplay/CheckpointTrigger.h"

void ARaceGameModeBase::BeginPlay() {
	Super::BeginPlay();

	GameHUD = Cast<AGameHUD>(GetWorld()->GetFirstPlayerController()->GetHUD());
	auto World = GetWorld();

	TArray<AActor *> CheckpointTriggers;
	UGameplayStatics::GetAllActorsOfClass(World, ACheckpointTrigger::StaticClass(), CheckpointTriggers);
	NumberOfCheckpoints = CheckpointTriggers.Num();

	LapStartTime = UGameplayStatics::GetRealTimeSeconds(World);
}

ARaceGameModeBase::ARaceGameModeBase() {
	PrimaryActorTick.bCanEverTick = true;
}

void ARaceGameModeBase::AddCheckpoint(int CheckpointNumber) {
	CheckpointsReached.insert(CheckpointNumber);
	GameHUD->UpdateCheckpoints(CheckpointsReached.size(), NumberOfCheckpoints);

	if (CheckpointsReached.size() == NumberOfCheckpoints) {
		CanFinishLap = true;
	}
}

void ARaceGameModeBase::FinishLap() {
	if (CanFinishLap) {
		bool AnotherLap = CurrentLap < NumberOfLaps;

		if (AnotherLap) {
			CurrentLap++;
			CheckpointsReached.clear();

			GameHUD->UpdateCheckpoints(0, NumberOfCheckpoints);
			GameHUD->UpdateLaps(CurrentLap, NumberOfLaps);
			return;
		}

		GameHUD->UpdateCheckpoints();
		GameHUD->UpdateLaps();
	}
}

int ARaceGameModeBase::GetNumberOfLaps() {
	return NumberOfLaps;
}

int ARaceGameModeBase::GetNumberOfCheckpoints() {
	return NumberOfCheckpoints;
}

bool ARaceGameModeBase::GetCanFinishLap() {
	return CanFinishLap;
}

void ARaceGameModeBase::AddTimeLost(float AddValue) {
	TimeLost += AddValue;

	GameHUD->UpdateLostTime(TimeLost);
}

void ARaceGameModeBase::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);

	float CurrentTime = UGameplayStatics::GetRealTimeSeconds(GetWorld());
	float NewTime = CurrentTime - LapStartTime;

	GameHUD->UpdateCurrentLapTime(NewTime);
}
