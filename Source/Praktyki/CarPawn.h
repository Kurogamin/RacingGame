// Copyright 2023 Teyon. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "CarMovement.h"
#include "GameFramework/Pawn.h"
#include "CarPawn.generated.h"

UCLASS()
class PRAKTYKI_API ACarPawn : public APawn
{
	GENERATED_BODY()

private:
	UCarMovement* CarMovement = nullptr;
	UStaticMeshComponent* CarMesh = nullptr;
	UStaticMeshComponent* SphereLocation = nullptr;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	ACarPawn();
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void ApplyThrottle(float Value);
	void ApplySteer(float Value);

};
