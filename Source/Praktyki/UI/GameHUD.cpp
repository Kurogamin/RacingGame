// Copyright 2023 Teyon. All Rights Reserved.

#include "GameHUD.h"
#include "../GameModes/PraktykiGameModeBase.h"
#include "CarCustomizationWidget.h"
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

	if (CarCustomizationWidgetClass) {
		CarCustomizationWidget =
				CreateWidget<UCarCustomizationWidget>(GetWorld(), CarCustomizationWidgetClass);

		if (CarCustomizationWidget) {
			CarCustomizationWidget->AddToViewport();
		}
	}
}

void AGameHUD::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);
}

void AGameHUD::UpdateCurrentSpeed(float NewCurrentSpeed, float NewCurrentGear, float NewPercent) {
	if (CarWidget) {
		CarWidget->UpdateCurrentSpeed(NewCurrentSpeed, NewCurrentGear, NewPercent);
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

void AGameHUD::UpdateCurrentLapTime(float NewLapTime, float NewLapLostTime) {
	if (CarWidget) {
		CarWidget->UpdateCurrentLapTime(NewLapTime, NewLapLostTime);
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

void AGameHUD::UpdateCurrentCheckpoint(float NewCurrentCheckpoint) {
	if (CarWidget) {
		CarWidget->UpdateCurrentCheckpoint(NewCurrentCheckpoint);
	}
}

void AGameHUD::UpdateRemainingTime(int NewRemainingTime) {
	if (CarWidget) {
		CarWidget->UpdateRemainingTime(NewRemainingTime);
	}
}

void AGameHUD::UpdateRemainingGameTime(float NewRemainingGameTime) {
	if (CarWidget) {
		CarWidget->UpdateRemainingGameTime(NewRemainingGameTime);
	}
}

void AGameHUD::UpdateCheckpointDifference(float NewCheckpointDifference) {
	if (CarWidget) {
		CarWidget->UpdateCheckpointDifference(NewCheckpointDifference);
	}
}

void AGameHUD::DrawHUD() {
	Super::DrawHUD();
}
