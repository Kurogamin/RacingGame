// Copyright 2023 Teyon. All Rights Reserved.

#include "CarPawn.h"
#include "../GameModes/PraktykiGameModeBase.h"
#include "../UI/GameHUD.h"

// Sets default values
ACarPawn::ACarPawn() {
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ACarPawn::BeginPlay() {
	Super::BeginPlay();

	auto Components = GetComponentsByTag(USkeletalMeshComponent::StaticClass(), FName("CarMesh"));

	if (Components.Num() > 0) {
		CarMesh = Cast<USkeletalMeshComponent>(Components[0]);
		CarMesh->OnComponentHit.AddDynamic(this, &ACarPawn::OnActorHit);
	}

	GameHUD = Cast<AGameHUD>(GetWorld()->GetFirstPlayerController()->GetHUD());
}

// Called every frame
void ACarPawn::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);

	if (CarMesh) {
		ApplyThrottle(DeltaTime);
		ApplySteering(DeltaTime);

		if (abs(CurrentSpeed.Length()) < 1.0f) {
			CurrentSpeed = FVector(0.0f);
		}

		UpdateSpeedText();
	}
}

void ACarPawn::SetupPlayerInputComponent(UInputComponent *PlayerInputComponent) {
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("Throttle", this, &ACarPawn::SetThrottle);
	PlayerInputComponent->BindAxis("Steer", this, &ACarPawn::SetSteering);

	PlayerInputComponent->BindAction("Brake", IE_Pressed, this, &ACarPawn::BrakePressed);
	PlayerInputComponent->BindAction("Brake", IE_Released, this, &ACarPawn::BrakeReleased);
}

void ACarPawn::SetThrottle(float ThrottleValue) {
	Throttle = ThrottleValue;
}

void ACarPawn::SetSteering(float SteeringValue) {
	Steering = SteeringValue;
}

void ACarPawn::BrakePressed() {
	IsBraking = true;
	Acceleration = -Acceleration;
	AccelerationStep = 0.1f * AccelerationStep;
}

void ACarPawn::BrakeReleased() {
	IsBraking = false;
	Acceleration = -Acceleration;
	AccelerationStep = 10.0f * AccelerationStep;
}

void ACarPawn::ApplyThrottle(float DeltaTime) {
	if (IsBraking) {
		auto CurrentVelocity = CarMesh->GetPhysicsLinearVelocity();
		CurrentSpeed = CurrentVelocity * BrakeSpeedSlowMultiplier;
		CarMesh->SetPhysicsLinearVelocity(CurrentSpeed);
		UpdateSpeedText();
		Acceleration *= BrakeAccelerationSlowMultiplier;
		return;
	}

	Acceleration += Throttle * AccelerationStep;

	if (Throttle == 0.0f) {
		if (abs(Acceleration) > 0.1f) {
			Acceleration *= AccelerationSlowMultiplier;
		} else {
			Acceleration = 0.0f;
		}
		auto CurrentVelocity = CarMesh->GetPhysicsLinearVelocity();
		CurrentSpeed = CurrentVelocity * SpeedSlowMultiplier;
		CarMesh->SetPhysicsLinearVelocity(CurrentSpeed);
		UpdateSpeedText();
		return;
	}

	Acceleration = FMath::Clamp(Acceleration, -MaxAcceleration, MaxAcceleration);

	auto ForwardVector = GetActorForwardVector();
	auto Force = ForwardVector * Acceleration;
	CurrentSpeed += Force * DeltaTime;

	auto Gravity = GetWorld()->GetGravityZ();
	CurrentSpeed.Z = Gravity * DeltaTime;

	CarMesh->SetPhysicsLinearVelocity(CurrentSpeed);
	CurrentSpeed = Force;
}

void ACarPawn::ApplySteering(float DeltaTime) {
	FVector Rotation{};

	if (Steering == 0.0f) {
		float SlowValue = IsBraking ? BrakeSteerSlowMultiplier : SteerSlowMultiplier;
		CurrentSteering = 0.0f;
		if (abs(CurrentSteering) < 0.1f) {
			CurrentSteering = 0.0f;
		}
		Rotation = FVector(0, 0, CurrentSteering);
		Rotation = IsBraking ? Rotation * DriftMultiplier : Rotation;
		CarMesh->SetPhysicsAngularVelocityInDegrees(Rotation);
		return;
	}

	float SteeringAngle = Steering * MaxSteeringAngle;

	CurrentSteering = SteeringAngle;
	Rotation = FVector(0, 0, CurrentSteering);
	Rotation = IsBraking ? Rotation * DriftMultiplier : Rotation;

	CarMesh->SetPhysicsAngularVelocityInDegrees(Rotation);

	//CarMesh->AddTorqueInDegrees(Rotation);
}

void ACarPawn::OnActorHit(UPrimitiveComponent *HitComp, AActor *OtherActor, UPrimitiveComponent *OtherComp,
		FVector NormalImpulse, const FHitResult &Hit) {
	if (OtherActor->ActorHasTag("Grass")) {
		AddTimeLost(0.01f);
	}
}

void ACarPawn::UpdateSpeedText() {
	if (GameHUD) {
		auto Speed = (int)(CurrentSpeed.Length() * 0.1f);
		GameHUD->UpdateCurrentSpeed((float)Speed);
	}
}

void ACarPawn::AddTimeLost(float AddValue) {
	ARaceGameModeBase *GameMode = Cast<ARaceGameModeBase>(GetWorld()->GetAuthGameMode());
	GameMode->AddTimeLost(AddValue);
}
