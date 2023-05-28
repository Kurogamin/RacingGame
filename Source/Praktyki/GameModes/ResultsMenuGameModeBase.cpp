// Copyright 2023 Teyon. All Rights Reserved.

#include "ResultsMenuGameModeBase.h"
#include "../Gameplay/LapData.h"
#include "../UI/GameHUD.h"
#include "RacingGameInstance.h"
#include <Kismet/GameplayStatics.h>

AResultsMenuGameModeBase::AResultsMenuGameModeBase() {
	PrimaryActorTick.bCanEverTick = true;
}

void AResultsMenuGameModeBase::BeginPlay() {
	Super::BeginPlay();
}

void AResultsMenuGameModeBase::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);

	if (!BestLapSet) {
		auto World = GetWorld();
		auto GameHUD = Cast<AGameHUD>(World->GetFirstPlayerController()->GetHUD());
		URacingGameInstance *GameInstance =
				Cast<URacingGameInstance>(UGameplayStatics::GetGameInstance(World));

		BestLapSet = GameHUD->UpdateBestLap(GameInstance->GetBestLap());
	}
}
