// Copyright 2023 Teyon. All Rights Reserved.

#include "CarPawn.h"
#include "../GameModes/PraktykiGameModeBase.h"
#include "../GameModes/RacingGameInstance.h"
#include "../UI/GameHUD.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"

// Sets default values
ACarPawn::ACarPawn() {
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if
	// you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ACarPawn::BeginPlay() {
	Super::BeginPlay();

	if (GetComponentByTag(CarMesh, "CarMesh")) {
		CarMesh->OnComponentHit.AddDynamic(this, &ACarPawn::OnActorHit);
	}

	GetComponentByTag(SpringArm, "SpringArm");
	GetComponentByTag(Camera, "Camera");
	GetComponentByTag(SteeringWheelMesh, "SteeringWheel");
	GetComponentByTag(FrontLeftWheelMesh, "FrontLeftWheel");
	GetComponentByTag(FrontRightWheelMesh, "FrontRightWheel");
	GetComponentByTag(FrontLeftWheelMeshTurn, "FrontLeftWheelTurn");
	GetComponentByTag(FrontRightWheelMeshTurn, "FrontRightWheelTurn");

	GameHUD = Cast<AGameHUD>(GetWorld()->GetFirstPlayerController()->GetHUD());

	SpeedStep = BaseSpeedStep;

	SetupMaterials();
}

// Called every frame
void ACarPawn::Tick(float DeltaTime) {
	if (!CanTick) {
		return;
	}

	Super::Tick(DeltaTime);

	if (CarMesh) {
		ApplyThrottle(DeltaTime);
		ApplySteering(DeltaTime);
		RotateWheels();
		RotateSteeringWheel();
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

	PlayerInputComponent->BindAction("Camera1", IE_Pressed, this, &ACarPawn::SwitchCamera<1>);
	PlayerInputComponent->BindAction("Camera2", IE_Pressed, this, &ACarPawn::SwitchCamera<2>);
	PlayerInputComponent->BindAction("Camera3", IE_Pressed, this, &ACarPawn::SwitchCamera<3>);
	PlayerInputComponent->BindAction("Camera4", IE_Pressed, this, &ACarPawn::SwitchCamera<4>);
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

	if (Throttle == 0.0f) {
		Speed = CurrentSpeed.Length() * ThrottleSlowMultiplier;
		CarMesh->SetPhysicsLinearVelocity(CurrentSpeed);
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
		Rotation = FVector(0, 0, CurrentSteering);
		Rotation = IsBraking ? Rotation * DriftMultiplier : Rotation;
		CarMesh->SetPhysicsAngularVelocityInDegrees(Rotation);
		return;
	}

	float SteeringAngle = Steering * MaxSteeringAngle;

	CurrentSteering = SteeringAngle;
	Rotation = FVector(0, 0, CurrentSteering);
	Rotation = IsBraking ? Rotation * DriftMultiplier : Rotation;

	auto CurrentRotation = CarMesh->GetPhysicsAngularVelocityInDegrees();

	CarMesh->SetPhysicsAngularVelocityInDegrees(
			FMath::Lerp(CurrentRotation, Rotation, SteeringRotationLerpStep));
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
		float GearSpeedRange = GearMaxSpeeds[0];
		float CurrentGearStart = 0.0f;

		if (CurrentGear > 0) {
			GearSpeedRange = GearMaxSpeeds[CurrentGear] - GearMaxSpeeds[CurrentGear - 1];
			CurrentGearStart = GearMaxSpeeds[CurrentGear - 1];
		}
		float SpeedPercent = (CurrentSpeed.Length() - CurrentGearStart) / GearSpeedRange;

		GameHUD->UpdateCurrentSpeed(int(CurrentSpeedLength * 0.1f), CurrentGear + 1, SpeedPercent);
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
	ShiftingGears = false;
	SpeedStep = BaseSpeedStep * GearAccelerationMultipliers[CurrentGear];
	GetWorld()->GetTimerManager().ClearTimer(GearShiftTimerHandle);
}

void ACarPawn::CheckGears() {
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

void ACarPawn::RotateSteeringWheel() {
	FRotator CurrentRotation = SteeringWheelMesh->GetRelativeRotation();
	FRotator NewRotation = FRotator(0.0, 0.0, Steering * 45.0f);
	SteeringWheelMesh->SetRelativeRotation(
			FMath::Lerp(CurrentRotation, NewRotation, SteeringRotationLerpStep));
}

void ACarPawn::SetupMaterials() {
	URacingGameInstance *GameInstance = Cast<URacingGameInstance>(GetGameInstance());
	auto CustomMaterialColors = GameInstance->GetCustomMaterialColors();
	auto CustomParts = GameInstance->GetCustomParts();

	UStaticMeshComponent *Mesh = nullptr;
	UMaterialInterface *MeshMaterial = nullptr;
	UMaterial *Material = Cast<UMaterial>(StaticLoadObject(
			UMaterial::StaticClass(), nullptr, TEXT("/Game/Materials/CustomMaterial")));

	if (CustomParts[0]) {
		auto DynamicMaterial = UMaterialInstanceDynamic::Create(Material, nullptr);
		DynamicMaterial->SetVectorParameterValue("Color", CustomMaterialColors[0]);
		GetComponentByTag(Mesh, "HoodMesh");
		MeshMaterial = Mesh->GetMaterials()[0];
		MeshMaterial = DynamicMaterial;
		Mesh->SetMaterial(0, MeshMaterial);
	}
	if (CustomParts[1]) {
		auto DynamicMaterial = UMaterialInstanceDynamic::Create(Material, nullptr);
		DynamicMaterial->SetVectorParameterValue("Color", CustomMaterialColors[1]);
		GetComponentByTag(Mesh, "SpoilerMesh");
		MeshMaterial = Mesh->GetMaterials()[0];
		MeshMaterial = DynamicMaterial;
		Mesh->SetMaterial(0, MeshMaterial);
	}
	if (CustomParts[2]) {
		auto DynamicMaterial = UMaterialInstanceDynamic::Create(Material, nullptr);
		DynamicMaterial->SetVectorParameterValue("Color", CustomMaterialColors[2]);
		GetComponentByTag(Mesh, "LeftDoorMesh");
		MeshMaterial = Mesh->GetMaterials()[0];
		MeshMaterial = DynamicMaterial;
		Mesh->SetMaterial(0, MeshMaterial);
	}
	if (CustomParts[3]) {
		auto DynamicMaterial = UMaterialInstanceDynamic::Create(Material, nullptr);
		DynamicMaterial->SetVectorParameterValue("Color", CustomMaterialColors[3]);
		GetComponentByTag(Mesh, "RightDoorMesh");
		MeshMaterial = Mesh->GetMaterials()[0];
		MeshMaterial = DynamicMaterial;
		Mesh->SetMaterial(0, MeshMaterial);
	}
}

void ACarPawn::RotateWheels() {
	FRotator TurnRotation = FrontLeftWheelMeshTurn->GetRelativeRotation();
	FRotator NewTurnRotation = TurnRotation;
	NewTurnRotation.Pitch = Steering * MaxSteeringAngle;

	FrontRightWheelMeshTurn->SetRelativeRotation(
			FMath::Lerp(TurnRotation, NewTurnRotation, WheelRotationLerpStep));
	FrontLeftWheelMeshTurn->SetRelativeRotation(
			FMath::Lerp(TurnRotation, NewTurnRotation, WheelRotationLerpStep));

	float WheelSpin = CurrentSpeed.Length() * 0.01f;
	FrontLeftWheelMesh->AddLocalRotation(FRotator(-WheelSpin, 0.0, 0.0));
	FrontRightWheelMesh->AddLocalRotation(FRotator(-WheelSpin, 0.0, 0.0));

	//FrontLeftWheelMesh->SetRelativeRotation(NewWheelRotation);
	//FrontRightWheelMesh->SetRelativeRotation(NewWheelRotation);
}

void ACarPawn::SwitchCamera(int CameraIndex) {
	if (CameraIndex < 1 || CameraIndex > 4) {
		return;
	}

	Camera->DetachFromComponent(FDetachmentTransformRules::KeepRelativeTransform);

	switch (CameraIndex) {
		case 1:
			Camera->AttachToComponent(SpringArm, FAttachmentTransformRules::KeepRelativeTransform);
			break;
		case 2:
			Camera->AttachToComponent(CarMesh, FAttachmentTransformRules::KeepRelativeTransform,
					"HoodGameplayCamera");
			break;
		case 3:
			Camera->AttachToComponent(CarMesh, FAttachmentTransformRules::KeepRelativeTransform,
					"CarInteriorGameplayCamera");
			break;
		case 4:
			Camera->AttachToComponent(
					CarMesh, FAttachmentTransformRules::KeepRelativeTransform, "LeftWheelCamera");
			break;
	}
}
