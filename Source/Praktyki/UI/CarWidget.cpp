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

void UCarWidget::UpdateCurrentSpeed(float NewCurrentSpeed, int NewCurrentGear, float NewPercent) {
	if (CurrentSpeedProgressBar && CurrentSpeedText && CurrentGearText) {
		FString CurrentGearString;

		if (NewPercent < 0.0f) {
			FLinearColor RedColor = FLinearColor::Red;
			CurrentGearText->SetText(FText::FromString(FString::FromInt(NewCurrentGear)));
			CurrentSpeedProgressBar->SetFillColorAndOpacity(RedColor);
			CurrentSpeedProgressBar->SetPercent(1.0f);
			CurrentGearText->SetColorAndOpacity(RedColor);
			return;
		}

		FLinearColor BarColor = FLinearColor::Green;
		FLinearColor GearColor = FLinearColor::White;
		if (NewPercent > 0.95f) {
			BarColor = FLinearColor::Red;
			GearColor = FLinearColor::Red;
		} else if (NewPercent > 0.65f) {
			BarColor = FLinearColor::Yellow;
			GearColor = FLinearColor::Yellow;
		}
		CurrentSpeedProgressBar->SetFillColorAndOpacity(BarColor);
		CurrentSpeedProgressBar->SetPercent(NewPercent);

		CurrentSpeedText->SetText(FText::FromString(FString::FromInt(NewCurrentSpeed)));
		CurrentGearText->SetText(FText::FromString(FString::FromInt(NewCurrentGear)));
		CurrentGearText->SetColorAndOpacity(GearColor);
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

void UCarWidget::UpdateCurrentLapTime(float NewLapTime, float NewLapLostTime) {
	if (CurrentLapTimeText) {
		FString StringCurrentLapTime = LapData::FloatToRoundedString(NewLapTime);
		FString StringCurrentLapLostTime = LapData::FloatToRoundedString(NewLapLostTime);

		CurrentLapTimeText->SetText(FText::FromString(StringCurrentLapTime + FString("<Red>") +
				StringCurrentLapLostTime + FString("</>")));
	}
}

void UCarWidget::UpdateBestLapTime(LapData NewBestLapData) {
	if (BestLapTimeText) {
		BestLapTimeText->SetText(FText::FromString(NewBestLapData.ToRichString()));
	}
}

void UCarWidget::UpdateCurrentCheckpoint(float NewCurrentCheckpoint) {
	if (CurrentCheckpointText) {
		FString StringCurrentCheckpoint = LapData::FloatToRoundedString(NewCurrentCheckpoint);
		CurrentCheckpointText->SetText(FText::FromString(StringCurrentCheckpoint));
	}
}