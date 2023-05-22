// Copyright 2023 Teyon. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "CarMovementComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PRAKTYKI_API UCarMovementComponent : public USceneComponent
{
	GENERATED_BODY()

private:
	UStaticMeshComponent* FrontLeftWheel = nullptr;
	UStaticMeshComponent* FrontRightWheel = nullptr;
	UStaticMeshComponent* BackLeftWheel = nullptr;
	UStaticMeshComponent* BackRightWheel = nullptr;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	UCarMovementComponent();
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};
