// Copyright 2023 Teyon. All Rights Reserved.

#include "CarWidget.h"

UCarWidget::UCarWidget(const FObjectInitializer &ObjectInitializer) : Super(ObjectInitializer) {
}

void UCarWidget::NativeConstruct() {
	Super::NativeConstruct();
}

void UCarWidget::UpdateCurrentSpeed(float NewCurrentSpeed) {
	if (CurrentSpeedText) {
		CurrentSpeedText->SetText(
				FText::FromString(FString("Current Speed: ") + FString::SanitizeFloat(NewCurrentSpeed)));
	}
}

void UCarWidget::UpdateLostTime(float NewLostTime) {
	if (CurrentTimeLostText) {
		float RoundedLostTime = FMath::RoundToZero(NewLostTime * 100) / 100;
		FString StringLostTime = FString::Printf(TEXT("%.2f"), RoundedLostTime);

		CurrentTimeLostText->SetText(FText::FromString(FString("Time Lost: ") + StringLostTime + FString(" s")));
	}
}

void UCarWidget::UpdateCheckpoints(int CurrentCheckpoints, int MaxCheckpoints) {
	if (CheckpointsText) {
		if (CurrentCheckpoints <= MaxCheckpoints) {
			CheckpointsText->SetText(FText::FromString(FString("Checkpoints: ") + FString::FromInt(CurrentCheckpoints) +
					FString("/") + FString::FromInt(MaxCheckpoints)));
		}
	}
}

void UCarWidget::UpdateLaps(int CurrentLap, int MaxLaps) {
	if (LapsText) {
		if (MaxLaps == 0 || CurrentLap == MaxLaps) {
			LapsText->SetText(FText::FromString(FString("")));
			return;
		}

		if (CurrentLap < MaxLaps) {
			LapsText->SetText(FText::FromString(
					FString("Laps: ") + FString::FromInt(CurrentLap) + FString("/") + FString::FromInt(MaxLaps)));
		}
	}
}

void UCarWidget::UpdateCurrentLapTime(float NewCurrentLapTime) {
	if (CurrentLapTimeText) {
		float RoundedCurrentLapTime = FMath::RoundToZero(NewCurrentLapTime * 1000) / 1000;
		FString StringCurrentLapTime = FString::Printf(TEXT("%.2f"), RoundedCurrentLapTime);

		CurrentLapTimeText->SetText(
				FText::FromString(FString("Current Lap Time: ") + StringCurrentLapTime + FString(" s")));
	}
}
