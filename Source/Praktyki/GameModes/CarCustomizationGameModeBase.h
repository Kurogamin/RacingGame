// Copyright 2023 Teyon. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"

#include "CarCustomizationGameModeBase.generated.h"

class ACameraPawn;
class UMaterialInstanceDynamic;

/**
 *
 */
UCLASS()
class PRAKTYKI_API ACarCustomizationGameModeBase : public AGameModeBase {
	GENERATED_BODY()
private:
	ACameraPawn *CameraPawn;
	int CurrentCameraPosition = 4;
	bool FoundMeshes = false;

	TArray<UStaticMeshComponent *> CarPartsMeshes;
	TArray<UMaterialInstanceDynamic *> CarPartsMaterials;
	TArray<UMaterialInstanceDynamic *> DefaultCarPartsMaterials;
	TArray<bool> CustomParts;

	void FindCarPartsMeshes();

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

public:
	ACarCustomizationGameModeBase();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FVector> CameraPositions;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FRotator> CameraRotations;

	UFUNCTION()
	void ChangeCameraPosition(int NewCameraPosition);

	void SetCustomPart(int PartIndex, bool IsCustom);
	void ReloadMaterial(int PartIndex);
	void SetMaterialColor(int PartIndex, FLinearColor Color);

	TArray<UMaterialInstanceDynamic *> GetCarPartsMaterials() const;
};
