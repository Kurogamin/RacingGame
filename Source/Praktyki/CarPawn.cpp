// Copyright 2023 Teyon. All Rights Reserved.


#include "CarPawn.h"

// Sets default values
ACarPawn::ACarPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ACarPawn::BeginPlay()
{
	Super::BeginPlay();

	UActorComponent* component = GetComponentByClass(UCarMovement::StaticClass());

	if (component)
	{
		CarMovement = Cast<UCarMovement>(component);
	}

	component = GetComponentsByTag(UStaticMeshComponent::StaticClass(), FName("CarMesh"))[0];

	if (component)
	{
		CarMesh = Cast<UStaticMeshComponent>(component);
	}

	component = GetComponentsByTag(UStaticMeshComponent::StaticClass(), FName("Sphere"))[0];

	if (component)
	{
		SphereLocation = Cast<UStaticMeshComponent>(component);
	}
}

// Called every frame
void ACarPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FVector DrivingForce = FVector(0.0f);
	float CurrentSteer = 0.0f;

	if (CarMovement && CarMesh)
	{
		float Throttle = CarMovement->GetThrottle();
		float CurrentSpeed = CarMovement->GetCurrentSpeed();
		CurrentSteer = CarMovement->GetCurrentSteer();

		FVector ForwardVector = CarMesh->GetForwardVector();

		FRotator CarRotation = CarMesh->GetComponentRotation();

		//DrivingForce = ForwardVector.RotateAngleAxis(CarRotation.Yaw, FVector(0.0f, 0.0f, 1.0f));
		DrivingForce = ForwardVector;
		DrivingForce.X *= CurrentSpeed;
		if (Throttle != 0.0f)
		{
			CarMesh->SetPhysicsLinearVelocity(FVector::ZeroVector);
			//CarMesh->AddImpulseAtLocation(DrivingForce, SphereLocation->GetComponentLocation());
			CarMesh->AddImpulse(DrivingForce);
		}

		CarMesh->AddWorldRotation(FRotator(0.0f, CurrentSteer * DeltaTime, 0.0f));
	}
}

// Called to bind functionality to input
void ACarPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("Throttle", this, &ACarPawn::ApplyThrottle);
	PlayerInputComponent->BindAxis("Steer", this, &ACarPawn::ApplySteer);
}

void ACarPawn::ApplyThrottle(float Value)
{
	if (CarMovement)
	{
		CarMovement->ApplyThrottle(Value);
	}
}

void ACarPawn::ApplySteer(float Value)
{
	if (CarMovement)
	{
		CarMovement->ApplySteer(Value);
	}
}

