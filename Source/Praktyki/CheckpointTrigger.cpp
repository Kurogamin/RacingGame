// Copyright 2023 Teyon. All Rights Reserved.

#include "CheckpointTrigger.h"
#include "PraktykiGameModeBase.h"

void ACheckpointTrigger::OnCheckpointEnter(UPrimitiveComponent *OverlappedComp, AActor *OtherActor,
		UPrimitiveComponent *OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult &SweepResult) {
	APraktykiGameModeBase *GameMode = Cast<APraktykiGameModeBase>(GetWorld()->GetAuthGameMode());

	if (OtherActor->ActorHasTag("PlayerCar")) {
		GameMode->AddCheckpoint(CheckpointId);
	}
}

void ACheckpointTrigger::BeginPlay() {
	Super::BeginPlay();

	auto Component = GetComponentsByTag(UBoxComponent::StaticClass(), FName("CheckpointTrigger"))[0];

	if (Component) {
		CheckpointTrigger = Cast<UBoxComponent>(Component);
		CheckpointTrigger->OnComponentBeginOverlap.AddDynamic(this, &ACheckpointTrigger::OnCheckpointEnter);
	}
}
