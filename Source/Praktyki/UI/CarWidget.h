// Copyright 2023 Teyon. All Rights Reserved.

#pragma once

#include "../Gameplay/LapData.h"
#include "Blueprint/UserWidget.h"
#include "Components/RichTextBlock.h"
#include "CoreMinimal.h"
#include "Runtime/UMG/Public/UMG.h"

#include "CarWidget.generated.h"
/**
 *
 */
UCLASS()
class PRAKTYKI_API UCarWidget : public UUserWidget {
	GENERATED_BODY()
private:
public:
	UCarWidget(const FObjectInitializer &ObjectInitializer);

	virtual void NativeConstruct() override;

	void UpdateCurrentSpeed(float NewCurrentSpeed);
	void UpdateLostTime(float AddValue);
	void UpdateCheckpoints(int CurrentCheckpoints, int MaxCheckpoints);
	void UpdateLaps(int CurrentLap = 0, int MaxLaps = 0);
	void UpdateCurrentLapTime(float NewCurrentLapTime);
	void UpdatePreviousLap(LapData NewPreviousLapData);

	UPROPERTY(EditAnywhere, BluePrintReadWrite, meta = (BindWidget))
	class URichTextBlock *CurrentSpeedText;

	UPROPERTY(EditAnywhere, BluePrintReadWrite, meta = (BindWidget))
	class UTextBlock *CurrentTimeLostText;

	UPROPERTY(EditAnywhere, BluePrintReadWrite, meta = (BindWidget))
	class UTextBlock *CheckpointsText;

	UPROPERTY(EditAnywhere, BluePrintReadWrite, meta = (BindWidget))
	class UTextBlock *LapsText;

	UPROPERTY(EditAnywhere, BluePrintReadWrite, meta = (BindWidget))
	class UTextBlock *CurrentLapTimeText;

	UPROPERTY(EditAnywhere, BluePrintReadWrite, meta = (BindWidget))
	class UTextBlock *PreviousLapTimeText;

	UPROPERTY(EditAnywhere, BluePrintReadWrite, meta = (BindWidget))
	class UTextBlock *PreviousLapLostTimeText;
};
