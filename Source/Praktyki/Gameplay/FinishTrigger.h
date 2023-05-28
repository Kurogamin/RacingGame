// Copyright 2023 Teyon. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Engine/TriggerBox.h"

#include "FinishTrigger.generated.h"

class UBoxComponent;

/**
 *
 */
UCLASS()
class PRAKTYKI_API AFinishTrigger : public ATriggerBox {
	GENERATED_BODY()

private:
	UBoxComponent *FinishTrigger = nullptr;

	UFUNCTION()
	void OnFinishEnter(UPrimitiveComponent *OverlappedComp, AActor *OtherActor,
			UPrimitiveComponent *OtherComp, int32 OtherBodyIndex, bool bFromSweep,
			const FHitResult &SweepResult);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
};
