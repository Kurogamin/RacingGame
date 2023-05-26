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
	float CurrentSteering = 0.0f;

	UPROPERTY(EditAnywhere)
	float AccelerationStep = 1000.0f;

	UPROPERTY(EditAnywhere)
	float MaxAcceleration = 50000.0f;

	//UPROPERTY(EditAnywhere)
	//float MaxSpeed = 1000.0f;

	UPROPERTY(EditAnywhere)
	float MaxSteeringAngle = 100000000.0f; // ?

	UPROPERTY(EditAnywhere)
	float DriftMultiplier = 2.0f;

	UPROPERTY(EditAnywhere)
	float BrakeSteerSlowMultiplier = 0.99f;

	UPROPERTY(EditAnywhere)
	float BrakeSpeedSlowMultiplier = 0.999f;

	UPROPERTY(EditAnywhere)
	float BrakeAccelerationSlowMultiplier = 0.99f;

	UPROPERTY(EditAnywhere)
	float SpeedSlowMultiplier = 0.99f;

	UPROPERTY(EditAnywhere)
	float AccelerationSlowMultiplier = 0.98f;

	UPROPERTY(EditAnywhere)
	float SteerSlowMultiplier = 0.99f;

	void UpdateSpeedText();
	void UpdateLostTimeText(float AddValue);

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
