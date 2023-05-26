// Copyright 2023 Teyon. All Rights Reserved.

#pragma once

#include "Components/BoxComponent.h"
#include "CoreMinimal.h"
#include "Engine/TriggerBox.h"

#include "CheckpointTrigger.generated.h"
/**
 *
 */
UCLASS()
class PRAKTYKI_API ACheckpointTrigger : public ATriggerBox {
	GENERATED_BODY()
private:
	UBoxComponent *CheckpointTrigger = nullptr;

	UPROPERTY(EditAnywhere)
	int CheckpointId = -1;

	UFUNCTION()
	void OnCheckpointEnter(UPrimitiveComponent *OverlappedComp, AActor *OtherActor, UPrimitiveComponent *OtherComp,
			int32 OtherBodyIndex, bool bFromSweep, const FHitResult &SweepResult);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
};
