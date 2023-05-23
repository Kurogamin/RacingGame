// Copyright 2023 Teyon. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CarMovement.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PRAKTYKI_API UCarMovement : public UActorComponent
{
	GENERATED_BODY()

private:	
	float Throttle = 0.f;
	float CurrentSpeed = 0.f;

	float Steer = 0.f;
	float CurrentSteer = 0.f;

	UPROPERTY(EditAnywhere)
	float MaxSteerAngle = 40.f;

	UPROPERTY(EditAnywhere)
	float MaxSpeed = 100.f;

	float CurrentAcceleration = 0.f;

	UPROPERTY(EditAnywhere)
	float MaxAcceleration = 10.f;
protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	UCarMovement();
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void ApplyThrottle(float Value);
	void ApplySteer(float Value);

	float GetCurrentSpeed() const { return CurrentSpeed; }
	float GetCurrentSteer() const { return CurrentSteer; }

	float GetThrottle() const { return Throttle; }

		
};
