// Copyright 2023 Teyon. All Rights Reserved.

#include "GameHUD.h"
#include "../GameModes/PraktykiGameModeBase.h"

AGameHUD::AGameHUD() {
}

void AGameHUD::BeginPlay() {
	Super::BeginPlay();

	if (CarWidgetClass) {
		CarWidget = CreateWidget<UCarWidget>(GetWorld(), CarWidgetClass);

		if (CarWidget) {
			CarWidget->AddToViewport();

			ARaceGameModeBase *GameMode = Cast<ARaceGameModeBase>(GetWorld()->GetAuthGameMode());

			UpdateLaps(0, GameMode->GetNumberOfLaps());
			UpdateCheckpoints(0, GameMode->GetNumberOfCheckpoints());
		}
	}
}

void AGameHUD::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);
}

void AGameHUD::UpdateCurrentSpeed(float NewCurrentSpeed) {
	if (CarWidget) {
		CarWidget->UpdateCurrentSpeed(NewCurrentSpeed);
	}
}

void AGameHUD::UpdateLostTime(float NewLostTime) {
	if (CarWidget) {
		CarWidget->UpdateLostTime(NewLostTime);
	}
}

void AGameHUD::UpdateCheckpoints(int CurrentCheckpoints, int MaxCheckpoints) {
	if (CarWidget) {
		CarWidget->UpdateCheckpoints(CurrentCheckpoints, MaxCheckpoints);
	}
}

void AGameHUD::UpdateLaps(int CurrentLap, int MaxLaps) {
	if (CarWidget) {
		CarWidget->UpdateLaps(CurrentLap, MaxLaps);
	}
}

void AGameHUD::UpdateCurrentLapTime(float NewCurrentLapTime) {
	if (CarWidget) {
		CarWidget->UpdateCurrentLapTime(NewCurrentLapTime);
	}
}

void AGameHUD::DrawHUD() {
	Super::DrawHUD();
}