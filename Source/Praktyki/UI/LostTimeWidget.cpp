// Copyright 2023 Teyon. All Rights Reserved.

#include "LostTimeWidget.h"

ULostTimeWidget::ULostTimeWidget(const FObjectInitializer &ObjectInitializer) : Super(ObjectInitializer) {
}

void ULostTimeWidget::NativeConstruct() {
	Super::NativeConstruct();

	LostTime = 0.0f;
}

void ULostTimeWidget::AddLostTime(float AddValue) {
	LostTime += AddValue;

	if (LostTimeText) {
		LostTimeText->SetText(
				FText::FromString(FString("Time Lost: ") + FString::SanitizeFloat(LostTime) + FString(" s")));
	}
}