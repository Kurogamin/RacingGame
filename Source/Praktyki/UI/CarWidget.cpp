// Copyright 2023 Teyon. All Rights Reserved.

#include "CarWidget.h"

UCarWidget::UCarWidget(const FObjectInitializer &ObjectInitializer) : Super(ObjectInitializer) {
}

void UCarWidget::NativeConstruct() {
	Super::NativeConstruct();

	this->CurrentSpeed = 0.0f;
}

void UCarWidget::SetCurrentSpeed(float NewCurrentSpeed) {
	this->CurrentSpeed = NewCurrentSpeed;

	if (this->CurrentSpeedText) {
		this->CurrentSpeedText->SetText(
				FText::FromString(FString("Current Speed: ") + FString::SanitizeFloat(this->CurrentSpeed)));
	}
}
