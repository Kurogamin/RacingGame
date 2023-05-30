// Fill out your copyright notice in the Description page of Project Settings.

#include "PraktykiGameModeBase.h"
#include "../Gameplay/CheckpointTrigger.h"
#include "../Gameplay/LapData.h"
#include "../UI/GameHUD.h"
#include "RacingGameInstance.h"
#include <Kismet/GameplayStatics.h>

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
	BestCheckpointTimes.Init(1000.0f, NumberOfCheckpoints);
	CurrentCheckpointTimes.Init(0.0f, NumberOfCheckpoints);

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
	if (CheckpointsReached.Contains(CheckpointNumber)) {
		return;
	}
	if (BestCheckpointTimes[CheckpointNumber] > CurrentLapTime) {
		BestCheckpointTimes[CheckpointNumber] = CurrentLapTime;
	}
	CurrentCheckpointTimes[CheckpointNumber] = CurrentLapTime;
	CheckpointsReached.Add(CheckpointNumber);
	int CheckpointsReachedNumber = CheckpointsReached.Num();

	GameHUD->UpdateCheckpoints(CheckpointsReachedNumber, NumberOfCheckpoints);
	GameHUD->UpdateCurrentCheckpoint(CurrentLapTime);

	if (CheckpointsReachedNumber == NumberOfCheckpoints) {
		CanFinishLap = true;
	}
}

void ARaceGameModeBase::FinishLap() {
	if (CanFinishLap) {
		AddLapData();
		bool AnotherLap = (NumberOfLaps == 1) || (CurrentLap < NumberOfLaps - 1);

		if (AnotherLap) {
			CurrentLap++;
			CheckpointsReached.Empty();

			GameHUD->UpdateCheckpoints(0, NumberOfCheckpoints);
			GameHUD->UpdateLaps(CurrentLap, NumberOfLaps);
			return;
		}

		EndCurrentRace();
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
	LapData CurrentLapData = LapData(CurrentLapTime, CurrentLapTimeLost, CurrentCheckpointTimes);
	if (CurrentLapData > BestLapData) {
		BestLapData = CurrentLapData;
		GameHUD->UpdateBestLap(BestLapData);
	}
	LapTimes.Add(CurrentLapData);

	CurrentLapTime = 0.0f;
	CurrentLapTimeLost = 0.0f;
	LapStartTime = UGameplayStatics::GetRealTimeSeconds(GetWorld());
}

void ARaceGameModeBase::AddTimeLost(float AddValue) {
	CurrentLapTimeLost += AddValue;
}

void ARaceGameModeBase::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);

	float CurrentTime = UGameplayStatics::GetRealTimeSeconds(GetWorld());

	CurrentLapTime = CurrentTime - LapStartTime;

	GameHUD->UpdateCurrentLapTime(CurrentLapTime, CurrentLapTimeLost);
}

void ARaceGameModeBase::EndCurrentRace() {
	auto GameInstance = Cast<URacingGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	GameInstance->SetBestLap(BestLapData);
	GameHUD->UpdateCheckpoints();
	GameHUD->UpdateLaps();
	UGameplayStatics::OpenLevel(GetWorld(), FName("ResultsMenuMap"));
}
