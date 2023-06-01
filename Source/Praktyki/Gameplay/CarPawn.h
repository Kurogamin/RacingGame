// Copyright 2023 Teyon. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"

#include "CarPawn.generated.h"

class AGameHUD;
class USpringArmComponent;
class UCameraComponent;
class UStaticMeshComponent;

UCLASS()
class PRAKTYKI_API ACarPawn : public APawn {
	GENERATED_BODY()

private:
	UPROPERTY(EditDefaultsOnly, Category = "Car|Pointers");
	USkeletalMeshComponent *CarMesh = nullptr;
	UStaticMeshComponent *SteeringWheelMesh = nullptr;
	UStaticMeshComponent *FrontLeftWheelMesh = nullptr;
	UStaticMeshComponent *FrontLeftWheelMeshTurn = nullptr;
	UStaticMeshComponent *FrontRightWheelMeshTurn = nullptr;
	UStaticMeshComponent *FrontRightWheelMesh = nullptr;
	USpringArmComponent *SpringArm = nullptr;
	UCameraComponent *Camera = nullptr;
	AGameHUD *GameHUD = nullptr;

	FVector CurrentSpeed{};
	// GEARS

	int CurrentGear = 0;

	UPROPERTY(EditAnywhere, Category = "Car|Gears")
	TArray<float> GearMaxSpeeds = { 1300.0f, 2100.0f, 3000.0f, 4100.0f, 5500.0f, 6510.0f };

	UPROPERTY(EditAnywhere, Category = "Car|Gears")
	TArray<float> GearAccelerationMultipliers = { 1.0f, 0.8f, 0.6f, 0.5f, 0.4f };

	UPROPERTY(EditAnywhere)
	float TimeToShift = 0.5f;

	FTimerHandle GearShiftTimerHandle;
	bool ShiftingGears = false;

	// HANDLING

	bool IsBraking = false;
	float Throttle = 0.0f;
	float Steering = 0.0f;
	float Speed = 0.0f;
	float CurrentSteering = 0.0f;

	UPROPERTY(EditAnywhere, Category = "Car|Speed")
	float BaseSpeedStep = 10.0f;

	float SpeedStep;

	UPROPERTY(EditAnywhere, Category = "Car|Speed")
	float MaxSpeed = 650.0f;

	UPROPERTY(EditAnywhere, Category = "Car|Steering")
	float MaxSteeringAngle = 40.0f; // ?

	UPROPERTY(EditAnywhere, Category = "Car|Steering")
	float DriftMultiplier = 2.0f;

	UPROPERTY(EditAnywhere, Category = "Car|Gears")
	float GearShiftSlowMultiplier = 0.1f;

	UPROPERTY(EditAnywhere, Category = "Car|Speed")
	float GrassSpeedMultiplier = 0.98f;

	UPROPERTY(EditAnywhere, Category = "Car|Steering")
	float BrakeSteerSlowMultiplier = 0.99f;

	UPROPERTY(EditAnywhere, Category = "Car|Speed")
	float BrakeSpeedSlowMultiplier = 0.999f;

	UPROPERTY(EditAnywhere, Category = "Car|Speed")
	float BrakeAccelerationSlowMultiplier = 0.99f;

	UPROPERTY(EditAnywhere, Category = "Car|Speed")
	float SpeedSlowMultiplier = 0.99f;

	UPROPERTY(EditAnywhere, Category = "Car|Speed")
	float AccelerationSlowMultiplier = 0.995f;

	UPROPERTY(EditAnywhere, Category = "Car|Speed")
	float WheelRotationLerpStep = 0.1f;

	UPROPERTY(EditAnywhere, Category = "Car|Steering")
	float SteerSlowMultiplier = 0.99f;

	UPROPERTY(EditAnywhere, Category = "Car|Steering")
	float SteeringRotationLerpStep = 0.1f;

	void UpdateSpeedText();
	void AddTimeLost(float AddValue);
	void CheckGears();
	void ShiftGear();
	void SwitchCamera(int CameraIndex);
	void RotateWheels();
	void RotateSteeringWheel();
	void SetupMaterials();

	template <int Index> void SwitchCamera() {
		SwitchCamera(Index);
	}

	template <typename T>
	typename std::enable_if<std::is_base_of<UObject, T>::value, bool>::type GetComponentByTag(
			T *&Component, FName Tag) {
		auto Components = GetComponentsByTag(T::StaticClass(), Tag);

		if (Components.Num() > 0) {
			Component = Cast<T>(Components[0]);
			return true;
		}
		return false;
	}

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
	void OnActorHit(UPrimitiveComponent *HitComp, AActor *OtherActor,
			UPrimitiveComponent *OtherComp, FVector NormalImpulse, const FHitResult &Hit);

	void BrakePressed();
	void BrakeReleased();

	bool CanTick = false;
};
