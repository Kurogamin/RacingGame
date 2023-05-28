// Copyright 2023 Teyon. All Rights Reserved.

#include "CheckpointTrigger.h"
#include "../GameModes/PraktykiGameModeBase.h"
#include "Components/BoxComponent.h"

void ACheckpointTrigger::OnCheckpointEnter(UPrimitiveComponent *OverlappedComp, AActor *OtherActor,
		UPrimitiveComponent *OtherComp, int32 OtherBodyIndex, bool bFromSweep,
		const FHitResult &SweepResult) {
	ARaceGameModeBase *GameMode = Cast<ARaceGameModeBase>(GetWorld()->GetAuthGameMode());

	if (OtherActor->ActorHasTag("PlayerCar")) {
		GameMode->AddCheckpoint(CheckpointId);
	}
}

void ACheckpointTrigger::BeginPlay() {
	Super::BeginPlay();

	auto Component =
			GetComponentsByTag(UBoxComponent::StaticClass(), FName("CheckpointTrigger"))[0];

	if (Component) {
		CheckpointTrigger = Cast<UBoxComponent>(Component);
		CheckpointTrigger->OnComponentBeginOverlap.AddDynamic(
				this, &ACheckpointTrigger::OnCheckpointEnter);
	}
}
