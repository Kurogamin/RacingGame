// Copyright 2023 Teyon. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"

#include "ResultsMenuGameModeBase.generated.h"

/**
 *
 */
UCLASS()
class PRAKTYKI_API AResultsMenuGameModeBase : public AGameModeBase {
	GENERATED_BODY()
private:
	bool BestLapSet = false;

protected:
	AResultsMenuGameModeBase();
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
};
