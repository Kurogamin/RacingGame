// Copyright 2023 Teyon. All Rights Reserved.

#include "CarCustomizationGameModeBase.h"
#include "../Gameplay/CameraPawn.h"
#include "../Gameplay/CarPawn.h"
#include "Camera/CameraActor.h"
#include <Kismet/GameplayStatics.h>

ACarCustomizationGameModeBase::ACarCustomizationGameModeBase() {
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = true;
}

void ACarCustomizationGameModeBase::BeginPlay() {
	Super::BeginPlay();

	CameraPawn = Cast<ACameraPawn>(UGameplayStatics::GetPlayerPawn(this, 0));
	CustomParts.Init(false, 4);
	CarPartsMeshes.Init(nullptr, 4);
	DefaultCarPartsMaterials.Init(nullptr, 4);

	UMaterial *CustomMaterial = Cast<UMaterial>(StaticLoadObject(
			UMaterial::StaticClass(), nullptr, TEXT("/Game/Materials/CustomMaterial")));

	for (int i = 0; i < 4; i++) {
		UMaterialInstanceDynamic *DynamicMaterial =
				UMaterialInstanceDynamic::Create(CustomMaterial, nullptr);
		CarPartsMaterials.Add(DynamicMaterial);
	}
}

void ACarCustomizationGameModeBase::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);
}

void ACarCustomizationGameModeBase::ChangeCameraPosition(int NewCameraPosition) {
	if (NewCameraPosition == CurrentCameraPosition) {
		return;
	}
	if (NewCameraPosition >= CameraPositions.Num() || NewCameraPosition >= CameraRotations.Num()) {
		return;
	}

	CameraPawn->SetActorLocation(CameraPositions[NewCameraPosition]);
	UGameplayStatics::GetPlayerController(this, 0)->ClientSetRotation(
			CameraRotations[NewCameraPosition]);
	CurrentCameraPosition = NewCameraPosition;
}

void ACarCustomizationGameModeBase::SetCustomPart(int PartIndex, bool IsCustom) {
	if (!FoundMeshes) {
		FindCarPartsMeshes();
		FoundMeshes = true;
	}

	CustomParts[PartIndex] = IsCustom;
	ReloadMaterial(PartIndex);
}

void ACarCustomizationGameModeBase::FindCarPartsMeshes() {
	TArray<AActor *> Actors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ACarPawn::StaticClass(), Actors);

	if (Actors.Num() == 0) {
		return;
	}

	ACarPawn *CarPawn = Cast<ACarPawn>(Actors[0]);

	TArray<UActorComponent *> MeshComponents;
	CarPawn->GetComponents(UStaticMeshComponent::StaticClass(), MeshComponents);

	for (auto Component : MeshComponents) {
		if (Component->ComponentHasTag("HoodMesh")) {
			CarPartsMeshes[0] = Cast<UStaticMeshComponent>(Component);
		} else if (Component->ComponentHasTag("SpoilerMesh")) {
			CarPartsMeshes[1] = Cast<UStaticMeshComponent>(Component);
		} else if (Component->ComponentHasTag("LeftDoorMesh")) {
			CarPartsMeshes[2] = Cast<UStaticMeshComponent>(Component);
		} else if (Component->ComponentHasTag("RightDoorMesh")) {
			CarPartsMeshes[3] = Cast<UStaticMeshComponent>(Component);
		}
	}

	for (int i = 0; i < CarPartsMeshes.Num(); i++) {
		UMaterialInterface *MeshMaterial = CarPartsMeshes[i]->GetMaterials()[0];
		DefaultCarPartsMaterials[i] = UMaterialInstanceDynamic::Create(MeshMaterial, nullptr);
	}
}

void ACarCustomizationGameModeBase::ReloadMaterial(int PartIndex) {
	UStaticMeshComponent *CurrentPart = CarPartsMeshes[PartIndex];
	TArray<UMaterialInterface *> Materials = CurrentPart->GetMaterials();
	if (CustomParts[PartIndex]) {
		Materials[0] = CarPartsMaterials[PartIndex];
	} else {
		Materials[0] = DefaultCarPartsMaterials[PartIndex];
	}
	CurrentPart->SetMaterial(0, Materials[0]);
}

void ACarCustomizationGameModeBase::SetMaterialColor(int PartIndex, FLinearColor Color) {
	CarPartsMaterials[PartIndex]->SetVectorParameterValue("Color", Color);
	ReloadMaterial(PartIndex);
}

TArray<UMaterialInstanceDynamic *> ACarCustomizationGameModeBase::GetCarPartsMaterials() const {
	return CarPartsMaterials;
}
