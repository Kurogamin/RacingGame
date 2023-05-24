// Copyright 2023 Teyon. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"

#include "CarPawn.generated.h"

class AGameHUD;

UCLASS()
class PRAKTYKI_API ACarPawn : public APawn {
	GENERATED_BODY()

private:
	UStaticMeshComponent *CarMesh = nullptr;
	FVector CurrentSpeed{};
	AGameHUD *GameHUD = nullptr;

	bool IsBraking = false;

	float Throttle = 0.0f;
	float Steering = 0.0f;

	float Acceleration = 0.0f;
	float AccelerationStep = 100000.0f;

	UPROPERTY(EditAnywhere)
	float MaxAcceleration = 3000000.0f;

	UPROPERTY(EditAnywhere)
	float MaxSpeed = 1000.0f;

	UPROPERTY(EditAnywhere)
	float MaxSteeringAngle = 100000000.0f; // ?

	UPROPERTY(EditAnywhere)
	float DriftMultiplier = 2.0f;

	void UpdateSpeedText();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	ACarPawn();
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent *PlayerInputComponent) override;

	void SetThrottle(float ThrottleValue);
	void SetSteering(float SteeringValue);

	void ApplyThrottle(float DeltaTime);
	void ApplySteering(float DeltaTime);

	UFUNCTION()
	void OnActorHit(UPrimitiveComponent *HitComp, AActor *OtherActor, UPrimitiveComponent *OtherComp,
			FVector NormalImpulse, const FHitResult &Hit);

	void BrakePressed();
	void BrakeReleased();
};
