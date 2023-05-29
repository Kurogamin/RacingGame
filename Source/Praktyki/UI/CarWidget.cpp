// Copyright 2023 Teyon. All Rights Reserved.

#include "CarWidget.h"
#include "../Gameplay/LapData.h"
#include "Components/ProgressBar.h"
#include "Components/RichTextBlock.h"
#include "Runtime/UMG/Public/UMG.h"

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
		CurrentSpeedText->SetText(
				FText::FromString(FString("Current Speed: ") + CurrentSpeedString));
	}
}

void UCarWidget::UpdateCurrentSpeedProgressBar(float NewPercent) {
	if (CurrentSpeedProgressBar) {
		CurrentSpeedProgressBar->SetPercent(NewPercent);
		FLinearColor BarColor = FLinearColor::Green;
		if (NewPercent > 0.95f) {
			BarColor = FLinearColor::Red;
		} else if (NewPercent > 0.65f) {
			BarColor = FLinearColor::Yellow;
		}
		CurrentSpeedProgressBar->SetFillColorAndOpacity(BarColor);
	}
}

void UCarWidget::UpdateLostTime(float NewLostTime) {
	if (CurrentTimeLostText) {
		FString StringLostTime = LapData::FloatToRoundedString(NewLostTime);

		CurrentTimeLostText->SetText(
				FText::FromString(FString("Time Lost: ") + StringLostTime + FString(" s")));
	}
}

void UCarWidget::UpdateCheckpoints(int CurrentCheckpoints, int MaxCheckpoints) {
	if (CheckpointsText) {
		if (CurrentCheckpoints <= MaxCheckpoints) {
			CheckpointsText->SetText(FText::FromString(FString("Checkpoints: ") +
					FString::FromInt(CurrentCheckpoints) + FString("/") +
					FString::FromInt(MaxCheckpoints)));
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
			LapsText->SetText(FText::FromString(FString("Laps: ") + FString::FromInt(CurrentLap) +
					FString("/") + FString::FromInt(MaxLaps)));
		}
	}
}

void UCarWidget::UpdateCurrentLapTime(float NewCurrentLapTime) {
	if (CurrentLapTimeText) {
		FString StringCurrentLapTime = LapData::FloatToRoundedString(NewCurrentLapTime);

		CurrentLapTimeText->SetText(FText::FromString(
				FString("Current Lap Time: ") + StringCurrentLapTime + FString(" s")));
	}
}

void UCarWidget::UpdatePreviousLap(LapData NewPreviousLapData) {
	if (PreviousLapTimeText && PreviousLapLostTimeText) {
		FString StringPreviousLapTime = LapData::FloatToRoundedString(NewPreviousLapData.LapTime);
		FString StringPreviousLapLostTime =
				LapData::FloatToRoundedString(NewPreviousLapData.LapTimeLost);

		PreviousLapTimeText->SetText(FText::FromString(
				FString("Previous Lap Time: ") + StringPreviousLapTime + FString(" s")));
		PreviousLapLostTimeText->SetText(FText::FromString(
				FString("Previous Lap Lost Time: ") + StringPreviousLapLostTime + FString(" s")));
	}
}

void UCarWidget::UpdateCurrentGear(int NewCurrentGear) {
	if (CurrentGearText) {
		CurrentGearText->SetText(
				FText::FromString(FString("Gear: ") + FString::FromInt(NewCurrentGear)));
	}
}
