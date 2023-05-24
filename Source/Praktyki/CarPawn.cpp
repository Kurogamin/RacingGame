// Copyright 2023 Teyon. All Rights Reserved.

#include "CarPawn.h"
#include "UI/GameHUD.h"

// Sets default values
ACarPawn::ACarPawn() {
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ACarPawn::BeginPlay() {
	Super::BeginPlay();

	auto Component = GetComponentsByTag(UStaticMeshComponent::StaticClass(), FName("CarMesh"))[0];

	if (Component) {
		this->CarMesh = Cast<UStaticMeshComponent>(Component);
	}

	this->GameHUD = Cast<AGameHUD>(GetWorld()->GetFirstPlayerController()->GetHUD());
}

// Called every frame
void ACarPawn::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);

	if (this->CarMesh) {
		ApplyThrottle(DeltaTime);
		ApplySteering(DeltaTime);

		if (abs(CurrentSpeed.Length()) < 1.0f) {
			this->CurrentSpeed = FVector(0.0f);
		}

		UpdateSpeedText();
	}
}

// Called to bind functionality to input
void ACarPawn::SetupPlayerInputComponent(UInputComponent *PlayerInputComponent) {
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("Throttle", this, &ACarPawn::SetThrottle);
	PlayerInputComponent->BindAxis("Steer", this, &ACarPawn::SetSteering);

	PlayerInputComponent->BindAction("Brake", IE_Pressed, this, &ACarPawn::BrakePressed);
	PlayerInputComponent->BindAction("Brake", IE_Released, this, &ACarPawn::BrakeReleased);
}

void ACarPawn::SetThrottle(float ThrottleValue) {
	this->Throttle = ThrottleValue;
}

void ACarPawn::SetSteering(float SteeringValue) {
	this->Steering = SteeringValue;
}

void ACarPawn::BrakePressed() {
	IsBraking = true;
	Acceleration = -Acceleration;
	AccelerationStep = 0.25f * AccelerationStep;
}

void ACarPawn::BrakeReleased() {
	IsBraking = false;
	Acceleration = -Acceleration;
	AccelerationStep = 4.0f * AccelerationStep;
}

void ACarPawn::ApplyThrottle(float DeltaTime) {
	if (IsBraking) {
		auto CurrentVelocity = CarMesh->GetPhysicsLinearVelocity();
		this->CurrentSpeed = CurrentVelocity * 0.999f;
		CarMesh->SetPhysicsLinearVelocity(this->CurrentSpeed);
		UpdateSpeedText();
		Acceleration = 0.0f;
		return;
	}

	Acceleration += Throttle * AccelerationStep;

	if (abs(Acceleration) <= 0.01f || Throttle == 0.0f) {
		auto CurrentVelocity = CarMesh->GetPhysicsLinearVelocity();
		this->CurrentSpeed = CurrentVelocity * 0.99f;
		CarMesh->SetPhysicsLinearVelocity(this->CurrentSpeed);
		UpdateSpeedText();
		return;
	}

	Acceleration = FMath::Clamp(Acceleration, -MaxAcceleration, MaxAcceleration);

	auto ForwardVector = GetActorForwardVector();
	auto Force = ForwardVector * Acceleration;

	CarMesh->SetPhysicsLinearVelocity(FVector(0.0f));

	CarMesh->AddImpulse(Force);

	this->CurrentSpeed = Force;

	if (CurrentSpeed.Length() > MaxSpeed) {
		CurrentSpeed.Normalize();
		CurrentSpeed *= MaxSpeed;
		CarMesh->SetPhysicsLinearVelocity(CurrentSpeed);
	}
}

void ACarPawn::ApplySteering(float DeltaTime) {
	if (Steering == 0.0f) {
		float SlowValue = IsBraking ? 0.99f : 0.999f;
		auto AngularVelocity = CarMesh->GetPhysicsAngularVelocityInRadians();
		CarMesh->SetPhysicsAngularVelocityInRadians(AngularVelocity * 0.90f);
		return;
	}

	float SteeringAngle = Steering * MaxSteeringAngle;
	FVector Rotation = FVector(0, 0, SteeringAngle);

	Rotation = IsBraking ? Rotation * DriftMultiplier : Rotation;

	auto CurrentVelocity = CarMesh->GetPhysicsLinearVelocity();

	CarMesh->AddTorqueInRadians(Rotation);
}

void ACarPawn::UpdateSpeedText() {
	if (GameHUD) {
		GameHUD->UpdateCurrentSpeed(CurrentSpeed.Length());
	}
}
