// Copyright 2023 Teyon. All Rights Reserved.

#include "CarWidget.h"

FString GetStringWithTag(FString Tag, FString Text) {
	return FString("<") + Tag + FString(">") + Text + FString("</>");
}

FString GetStringWithTag(FString Tag, float Text) {
	return FString("<") + Tag + FString(">") + FString::SanitizeFloat(Text) + FString("</>");
}

UCarWidget::UCarWidget(const FObjectInitializer &ObjectInitializer) : Super(ObjectInitializer) {
}

void UCarWidget::NativeConstruct() {
	Super::NativeConstruct();
}

void UCarWidget::UpdateCurrentSpeed(float NewCurrentSpeed) {
	if (CurrentSpeedText) {
		FString CurrentSpeedString = GetStringWithTag("Green", NewCurrentSpeed);
		CurrentSpeedText->SetText(FText::FromString(FString("Current Speed: ") + CurrentSpeedString));
	}
}

void UCarWidget::UpdateLostTime(float NewLostTime) {
	if (CurrentTimeLostText) {
		float RoundedLostTime = FMath::RoundToZero(NewLostTime * 1000) / 1000;
		FString StringLostTime = FString::Printf(TEXT("%.3f"), RoundedLostTime);

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
		FString StringCurrentLapTime = FString::Printf(TEXT("%.3f"), RoundedCurrentLapTime);

		CurrentLapTimeText->SetText(
				FText::FromString(FString("Current Lap Time: ") + StringCurrentLapTime + FString(" s")));
	}
}

void UCarWidget::UpdatePreviousLap(float PreviousLapTime, float PreviousLapLostTime) {
	if (PreviousLapTimeText && PreviousLapLostTimeText) {
		float RoundedPreviousLapTime = FMath::RoundToZero(PreviousLapTime * 1000) / 1000;
		float RoundedPreviousLapLostTime = FMath::RoundToZero(PreviousLapLostTime * 1000) / 1000;
		FString StringPreviousLapTime = FString::Printf(TEXT("%.3f"), RoundedPreviousLapTime);
		FString StringPreviousLapLostTime = FString::Printf(TEXT("%.3f"), RoundedPreviousLapLostTime);

		PreviousLapTimeText->SetText(
				FText::FromString(FString("Previous Lap Time: ") + StringPreviousLapTime + FString(" s")));
		PreviousLapLostTimeText->SetText(
				FText::FromString(FString("Previous Lap Lost Time: ") + StringPreviousLapLostTime + FString(" s")));
	}
}
