// Copyright 2023 Teyon. All Rights Reserved.

#include "CarCustomizationGameModeBase.h"
#include "../Gameplay/CameraPawn.h"
#include "Camera/CameraActor.h"
#include <Kismet/GameplayStatics.h>

void ACarCustomizationGameModeBase::BeginPlay() {
	Super::BeginPlay();

	CameraPawn = Cast<ACameraPawn>(UGameplayStatics::GetPlayerPawn(this, 0));
}

void ACarCustomizationGameModeBase::ChangeCameraPosition(CameraPosition NewCameraPosition) {
	if (NewCameraPosition == CurrentCameraPosition) {
		return;
	}
	if (NewCameraPosition >= CameraPositions.Num() || NewCameraPosition >= CameraRotations.Num()) {
		return;
	}

	CameraPawn->SetActorLocation(CameraPositions[NewCameraPosition]);
	CameraPawn->SetActorRotation(CameraRotations[NewCameraPosition]);
}