// Fill out your copyright notice in the Description page of Project Settings.

#include "PraktykiGameModeBase.h"
#include "../Gameplay/CheckpointTrigger.h"
#include "RacingGameInstance.h"

void ARaceGameModeBase::BeginPlay() {
	Super::BeginPlay();

	GameHUD = Cast<AGameHUD>(GetWorld()->GetFirstPlayerController()->GetHUD());
	auto World = GetWorld();
	URacingGameInstance *GameInstance =
			Cast<URacingGameInstance>(UGameplayStatics::GetGameInstance(World));

	TArray<AActor *> CheckpointTriggers;
	UGameplayStatics::GetAllActorsOfClass(
			World, ACheckpointTrigger::StaticClass(), CheckpointTriggers);
	NumberOfCheckpoints = CheckpointTriggers.Num();

	LapStartTime = UGameplayStatics::GetRealTimeSeconds(World);
	GameStartTime = UGameplayStatics::GetRealTimeSeconds(World);

	NumberOfLaps = GameInstance->GetNumberOfLaps();

	CurrentRaceType = GameInstance->GetCurrentRaceType();

	if (CurrentRaceType == RaceType::Time) {
		NumberOfSeconds = GameInstance->GetNumberOfSeconds();

		GetWorldTimerManager().SetTimer(
				EndGameTimer, this, &ARaceGameModeBase::EndCurrentRace, NumberOfSeconds, false);
	}
}

ARaceGameModeBase::ARaceGameModeBase() {
	PrimaryActorTick.bCanEverTick = true;
}

void ARaceGameModeBase::AddCheckpoint(int CheckpointNumber) {
	CheckpointsReached.Add(CheckpointNumber);
	int CheckpointsReachedNumber = CheckpointsReached.Num();
	GameHUD->UpdateCheckpoints(CheckpointsReachedNumber, NumberOfCheckpoints);

	if (CheckpointsReachedNumber == NumberOfCheckpoints) {
		CanFinishLap = true;
	}
}

void ARaceGameModeBase::FinishLap() {
	if (CanFinishLap) {
		AddLapData();
		bool AnotherLap = CurrentLap < NumberOfLaps - 1;

		if (AnotherLap) {
			CurrentLap++;
			CheckpointsReached.Empty();

			GameHUD->UpdateCheckpoints(0, NumberOfCheckpoints);
			GameHUD->UpdateLaps(CurrentLap, NumberOfLaps);
			return;
		}

		GameHUD->UpdateCheckpoints();
		GameHUD->UpdateLaps();
		UGameplayStatics::OpenLevel(GetWorld(), FName("MainMenuMap"));
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

void ARaceGameModeBase::AddLapData() {
	LapData CurrentLapData = LapData(CurrentLapTime, CurrentLapTimeLost);
	LapTimes.Add(CurrentLapData);

	CurrentLapTime = 0.0f;
	CurrentLapTimeLost = 0.0f;
	LapStartTime = UGameplayStatics::GetRealTimeSeconds(GetWorld());

	GameHUD->UpdatePreviousLap(CurrentLapData.LapTime, CurrentLapData.LapTimeLost);
}

void ARaceGameModeBase::AddTimeLost(float AddValue) {
	CurrentLapTimeLost += AddValue;

	GameHUD->UpdateLostTime(CurrentLapTimeLost);
}

void ARaceGameModeBase::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);

	float CurrentTime = UGameplayStatics::GetRealTimeSeconds(GetWorld());

	CurrentLapTime = CurrentTime - LapStartTime;

	GameHUD->UpdateCurrentLapTime(CurrentLapTime);
}

void ARaceGameModeBase::EndCurrentRace() {
	GameHUD->UpdateCheckpoints();
	GameHUD->UpdateLaps();
	UGameplayStatics::OpenLevel(GetWorld(), FName("MainMenuMap"));
}
