// Copyright 2023 Teyon. All Rights Reserved.

#include "CarPawn.h"
#include "../GameModes/PraktykiGameModeBase.h"
#include "../UI/GameHUD.h"

// Sets default values
ACarPawn::ACarPawn() {
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if
	// you don't need it.
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

	SpeedStep = BaseSpeedStep;
}

// Called every frame
void ACarPawn::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);

	if (CarMesh) {
		ApplyThrottle(DeltaTime);
		ApplySteering(DeltaTime);
		CheckGears();

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
}

void ACarPawn::BrakeReleased() {
	IsBraking = false;
	Speed = CurrentSpeed.Length() * BrakeAccelerationSlowMultiplier;
}

void ACarPawn::ApplyThrottle(float DeltaTime) {
	if (IsBraking) {
		auto CurrentVelocity = CarMesh->GetPhysicsLinearVelocity();
		CurrentSpeed = CurrentVelocity * BrakeSpeedSlowMultiplier;
		CarMesh->SetPhysicsLinearVelocity(CurrentSpeed);
		return;
	}

	float LocalAccelerationStep = SpeedStep;
	if (ShiftingGears) {
		LocalAccelerationStep *= GearShiftSlowMultiplier;
	}
	Speed += Throttle * LocalAccelerationStep;
	Speed = FMath::Clamp(Speed, -MaxSpeed * 10.0f, MaxSpeed * 10.0f);

	auto Force = GetActorForwardVector() * Speed;
	auto Gravity = GetWorld()->GetGravityZ();

	CurrentSpeed += Force * DeltaTime;
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
}

void ACarPawn::OnActorHit(UPrimitiveComponent *HitComp, AActor *OtherActor,
		UPrimitiveComponent *OtherComp, FVector NormalImpulse, const FHitResult &Hit) {
	if (OtherActor->ActorHasTag("Grass")) {
		AddTimeLost(0.01f);
		Speed *= GrassSpeedMultiplier;
	}
}

void ACarPawn::UpdateSpeedText() {
	if (GameHUD) {
		float CurrentSpeedLength = CurrentSpeed.Length();
		GameHUD->UpdateCurrentSpeed(int(CurrentSpeedLength * 0.1f));
	}
}

void ACarPawn::AddTimeLost(float AddValue) {
	ARaceGameModeBase *GameMode = Cast<ARaceGameModeBase>(GetWorld()->GetAuthGameMode());
	GameMode->AddTimeLost(AddValue);
}

void ACarPawn::ShiftGear() {
	int NumberOfGears = GearMaxSpeeds.Num();
	int NewGear = NumberOfGears - 1;
	float CurrentSpeedLength = CurrentSpeed.Length();

	for (int i = 0; i < NumberOfGears; i++) {
		if (CurrentSpeedLength < GearMaxSpeeds[i]) {
			NewGear = i;
			break;
		}
	}

	CurrentGear = NewGear;
	SpeedStep = BaseSpeedStep * GearAccelerationMultipliers[CurrentGear];
	ShiftingGears = false;
	GetWorld()->GetTimerManager().ClearTimer(GearShiftTimerHandle);
	GameHUD->UpdateCurrentGear(CurrentGear + 1);
}

void ACarPawn::CheckGears() {
	float GearSpeedRange = GearMaxSpeeds[0];
	float CurrentGearStart = 0.0f;
	if (CurrentGear > 0) {
		GearSpeedRange = GearMaxSpeeds[CurrentGear] - GearMaxSpeeds[CurrentGear - 1];
		CurrentGearStart = GearMaxSpeeds[CurrentGear - 1];
	}
	float SpeedPercent = (CurrentSpeed.Length() - CurrentGearStart) / GearSpeedRange;
	GameHUD->UpdateCurrentSpeedProgressBar(SpeedPercent);

	if (ShiftingGears) {
		return;
	}

	float CurrentSpeedLength = CurrentSpeed.Length();

	float GearMaxSpeed = GearMaxSpeeds[CurrentGear];
	float GearMinSpeed = CurrentGear > 0 ? GearMaxSpeeds[CurrentGear - 1] : 0.0f;

	if (CurrentSpeedLength < GearMaxSpeed && CurrentSpeedLength >= GearMinSpeed) {
		return;
	}

	ShiftingGears = true;
	auto World = GetWorld();
	if (!World->GetTimerManager().IsTimerActive(GearShiftTimerHandle)) {
		World->GetTimerManager().SetTimer(
				GearShiftTimerHandle, this, &ACarPawn::ShiftGear, TimeToShift, false);
	}
}
