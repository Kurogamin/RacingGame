// Copyright 2023 Teyon. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"

#include "CarCustomizationGameModeBase.generated.h"

class ACameraPawn;

UENUM()
enum CameraPosition { Hood, Spoiler, LeftDoor, RightDoor };

/**
 *
 */
UCLASS()
class PRAKTYKI_API ACarCustomizationGameModeBase : public AGameModeBase {
	GENERATED_BODY()
private:
	ACameraPawn *CameraPawn;
	CameraPosition CurrentCameraPosition = CameraPosition::Hood;

protected:
	virtual void BeginPlay() override;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FVector> CameraPositions;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FRotator> CameraRotations;

	UFUNCTION()
	void ChangeCameraPosition(CameraPosition NewCameraPosition);
};
