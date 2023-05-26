// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "UI/GameHUD.h"
#include <set>

#include "PraktykiGameModeBase.generated.h"

/**
 *
 */
UCLASS()
class PRAKTYKI_API APraktykiGameModeBase : public AGameModeBase {
	GENERATED_BODY()
private:
	AGameHUD *GameHUD = nullptr;

	UPROPERTY(EditAnywhere)
	int NumberOfCheckpoints = 0;

	bool CanFinishLap = false;
	std::set<int> CheckpointsReached;

protected:
	virtual void BeginPlay() override;

public:
	APraktykiGameModeBase();

	void AddCheckpoint(int CheckpointNumber);
};
