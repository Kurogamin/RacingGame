// Copyright 2023 Teyon. All Rights Reserved.


#include "CarMovement.h"

// Sets default values for this component's properties
UCarMovement::UCarMovement()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UCarMovement::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UCarMovement::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (Throttle != 0.f)
	{
		CurrentAcceleration += Throttle * DeltaTime * 1000;
		CurrentAcceleration = FMath::Clamp(CurrentAcceleration, -MaxAcceleration, MaxAcceleration);
	}

	CurrentSpeed += CurrentAcceleration;
	CurrentSpeed = FMath::Clamp(CurrentSpeed, -MaxSpeed, MaxSpeed);
}

void UCarMovement::ApplyThrottle(float Value)
{
	Value = FMath::Clamp<float>(Value, -1, 1);

	Throttle = Value;
}

void UCarMovement::ApplySteer(float Value)
{
	Value = FMath::Clamp<float>(Value, -1, 1);

	CurrentSteer = Value * MaxSteerAngle;
}

