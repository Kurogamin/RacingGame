// Fill out your copyright notice in the Description page of Project Settings.

#include "PraktykiGameModeBase.h"
#include "../Gameplay/CarPawn.h"
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

	GameStartTime = UGameplayStatics::GetRealTimeSeconds(World);
	NumberOfLaps = GameInstance->GetNumberOfLaps();
	CurrentRaceType = GameInstance->GetCurrentRaceType();

	CarPawn = Cast<ACarPawn>(UGameplayStatics::GetPlayerPawn(this, 0));

	if (CurrentRaceType == RaceType::Time) {
		NumberOfSeconds = GameInstance->GetNumberOfSeconds();

		GetWorldTimerManager().SetTimer(EndGameTimer, this, &ARaceGameModeBase::EndCurrentRace,
				NumberOfSeconds + StartDelay, false);
	}

	GetWorldTimerManager().SetTimer(
			StartGameTimer, this, &ARaceGameModeBase::StartRace, StartDelay, false);
}

ARaceGameModeBase::ARaceGameModeBase() {
	PrimaryActorTick.bCanEverTick = true;
}

void ARaceGameModeBase::AddCheckpoint(int CheckpointNumber) {
	if (CheckpointsReached.Contains(CheckpointNumber)) {
		return;
	}
	float CheckpointDifference = BestCheckpointTimes[CheckpointNumber] - CurrentLapTime;
	GameHUD->UpdateCheckpointDifference(CheckpointDifference);

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

void ARaceGameModeBase::StartRace() {
	auto World = GetWorld();
	TArray<AActor *> CheckpointTriggers;
	UGameplayStatics::GetAllActorsOfClass(
			World, ACheckpointTrigger::StaticClass(), CheckpointTriggers);
	NumberOfCheckpoints = CheckpointTriggers.Num();
	BestCheckpointTimes.Init(1000.0f, NumberOfCheckpoints);
	CurrentCheckpointTimes.Init(0.0f, NumberOfCheckpoints);
	LapStartTime = UGameplayStatics::GetRealTimeSeconds(World);
	GameHUD->UpdateRemainingTime(-1);

	CarPawn->CanTick = true;
	GameStarted = true;
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
	} else if (CurrentLapData > SecondBestLapData) {
		SecondBestLapData = CurrentLapData;
	}
	LapTimes.Add(CurrentLapData);

	GameHUD->UpdateCurrentCheckpoint(CurrentLapTime);

	CurrentLapTime = 0.0f;
	CurrentLapTimeLost = 0.0f;
	LapStartTime = UGameplayStatics::GetRealTimeSeconds(GetWorld());
}

void ARaceGameModeBase::AddTimeLost(float AddValue) {
	CurrentLapTimeLost += AddValue;
}

void ARaceGameModeBase::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);

	if (!GameStarted) {
		int SecondsUntilStart = GetWorld()->GetTimerManager().GetTimerRemaining(StartGameTimer);
		GameHUD->UpdateRemainingTime(SecondsUntilStart);
		return;
	}

	float CurrentTime = UGameplayStatics::GetRealTimeSeconds(GetWorld());

	CurrentLapTime = CurrentTime - LapStartTime;

	float RemainingGameTime = GetWorld()->GetTimerManager().GetTimerRemaining(EndGameTimer);
	GameHUD->UpdateRemainingGameTime(RemainingGameTime);

	GameHUD->UpdateCurrentLapTime(CurrentLapTime, CurrentLapTimeLost);
}

void ARaceGameModeBase::EndCurrentRace() {
	auto GameInstance = Cast<URacingGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	GameInstance->SetBestLap(BestLapData);
	GameHUD->UpdateCheckpoints();
	GameHUD->UpdateLaps();
	UGameplayStatics::OpenLevel(GetWorld(), FName("ResultsMenuMap"));
}
