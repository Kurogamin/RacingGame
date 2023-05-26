// Copyright 2023 Teyon. All Rights Reserved.

#include "CarWidget.h"

UCarWidget::UCarWidget(const FObjectInitializer &ObjectInitializer) : Super(ObjectInitializer) {
}

void UCarWidget::NativeConstruct() {
	Super::NativeConstruct();

	CurrentSpeed = 0.0f;
}

void UCarWidget::SetCurrentSpeed(float NewCurrentSpeed) {
	CurrentSpeed = NewCurrentSpeed;

	if (CurrentSpeedText) {
		CurrentSpeedText->SetText(FText::FromString(FString("Current Speed: ") + FString::SanitizeFloat(CurrentSpeed)));
	}
}

void UCarWidget::AddLostTime(float AddValue) {
	CurrentLostTime += AddValue;

	if (CurrentTimeLostText) {
		float RoundedLostTime = FMath::RoundToZero(CurrentLostTime * 100) / 100; // Round to 2 decimal places
		FString StringLostTime = FString::Printf(TEXT("%.2f"), RoundedLostTime);

		CurrentTimeLostText->SetText(FText::FromString(FString("Time Lost: ") + StringLostTime + FString(" s")));
	}
}
