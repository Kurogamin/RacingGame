// Fill out your copyright notice in the Description page of Project Settings.

#include "PraktykiGameModeBase.h"

void APraktykiGameModeBase::BeginPlay() {
	Super::BeginPlay();

	GameHUD = Cast<AGameHUD>(GetWorld()->GetFirstPlayerController()->GetHUD());
}

APraktykiGameModeBase::APraktykiGameModeBase() {
}

void APraktykiGameModeBase::AddCheckpoint(int CheckpointNumber) {
	CheckpointsReached.insert(CheckpointNumber);
	GameHUD->UpdateCheckpoints(CheckpointsReached.size(), NumberOfCheckpoints);

	if (CheckpointsReached.size() == NumberOfCheckpoints) {
		CanFinishLap = true;
	}
}
