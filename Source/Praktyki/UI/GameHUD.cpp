// Copyright 2023 Teyon. All Rights Reserved.

#include "GameHUD.h"
#include "../GameModes/PraktykiGameModeBase.h"
#include "CarWidget.h"
#include "MainMenuWidget.h"
#include "ResultsMenuWidget.h"

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

	if (MainMenuWidgetClass) {
		MainMenuWidget = CreateWidget<UMainMenuWidget>(GetWorld(), MainMenuWidgetClass);

		if (MainMenuWidget) {
			MainMenuWidget->AddToViewport();
		}
	}

	if (ResultsMenuWidgetClass) {
		ResultsMenuWidget = CreateWidget<UResultsMenuWidget>(GetWorld(), ResultsMenuWidgetClass);

		if (ResultsMenuWidget) {
			ResultsMenuWidget->AddToViewport();
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

void AGameHUD::UpdateCurrentSpeedProgressBar(float NewPercent) {
	if (CarWidget) {
		CarWidget->UpdateCurrentSpeedProgressBar(NewPercent);
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

void AGameHUD::UpdatePreviousLap(LapData NewPreviousLapData) {
	if (CarWidget) {
		CarWidget->UpdatePreviousLap(NewPreviousLapData);
	}
}

void AGameHUD::UpdateCurrentGear(int NewCurrentGear) {
	if (CarWidget) {
		CarWidget->UpdateCurrentGear(NewCurrentGear);
	}
}

bool AGameHUD::UpdateBestLap(LapData NewBestLap) {
	if (ResultsMenuWidget) {
		if (NewBestLap.LapTime == 0.0f) {
			ResultsMenuWidget->UpdateBestLap();
			return true;
		}
		ResultsMenuWidget->UpdateBestLap(NewBestLap);
		return true;
	}

	return false;
}

void AGameHUD::DrawHUD() {
	Super::DrawHUD();
}
