// Copyright 2023 Teyon. All Rights Reserved.

#include "FinishTrigger.h"
#include "../GameModes/PraktykiGameModeBase.h"

void AFinishTrigger::OnFinishEnter(UPrimitiveComponent *OverlappedComp, AActor *OtherActor,
		UPrimitiveComponent *OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult &SweepResult) {
	ARaceGameModeBase *GameMode = Cast<ARaceGameModeBase>(GetWorld()->GetAuthGameMode());

	if (OtherActor->ActorHasTag("PlayerCar")) {
		if (GameMode->GetCanFinishLap()) {
			GameMode->FinishLap();
		}
	}
}

void AFinishTrigger::BeginPlay() {
	Super::BeginPlay();

	auto Component = GetComponentsByTag(UBoxComponent::StaticClass(), FName("FinishTrigger"))[0];

	if (Component) {
		FinishTrigger = Cast<UBoxComponent>(Component);
		FinishTrigger->OnComponentBeginOverlap.AddDynamic(this, &AFinishTrigger::OnFinishEnter);
	}
}
