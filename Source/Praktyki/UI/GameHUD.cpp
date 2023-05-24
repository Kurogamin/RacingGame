// Copyright 2023 Teyon. All Rights Reserved.

#include "GameHUD.h"

AGameHUD::AGameHUD() {
}

void AGameHUD::BeginPlay() {
	Super::BeginPlay();

	if (CarWidgetClass) {
		CarWidget = CreateWidget<UCarWidget>(GetWorld(), CarWidgetClass);

		if (CarWidget) {
			CarWidget->AddToViewport();
		}
	}
}

void AGameHUD::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);
}

void AGameHUD::UpdateCurrentSpeed(float NewCurrentSpeed) {
	if (CarWidget) {
		CarWidget->SetCurrentSpeed(NewCurrentSpeed);
	}
}

void AGameHUD::DrawHUD() {
	Super::DrawHUD();
}
