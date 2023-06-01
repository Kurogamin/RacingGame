// Copyright 2023 Teyon. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"

#include "CarCustomizationGameModeBase.generated.h"

class ACameraPawn;

/**
 *
 */
UCLASS()
class PRAKTYKI_API ACarCustomizationGameModeBase : public AGameModeBase {
	GENERATED_BODY()
private:
	ACameraPawn *CameraPawn;
	int CurrentCameraPosition = 4;

protected:
	virtual void BeginPlay() override;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FVector> CameraPositions;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FRotator> CameraRotations;

	UFUNCTION()
	void ChangeCameraPosition(int NewCameraPosition);
};
