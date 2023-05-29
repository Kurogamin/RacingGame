// Copyright 2023 Teyon. All Rights Reserved.

#pragma once

#include "../Gameplay/LapData.h"
#include "Blueprint/UserWidget.h"
#include "CoreMinimal.h"

#include "CarWidget.generated.h"

class URichTextBlock;
class UTextBlock;
class UProgressBar;

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
	void UpdateCurrentSpeedProgressBar(float NewPercent);
	void UpdateLostTime(float AddValue);
	void UpdateCheckpoints(int CurrentCheckpoints, int MaxCheckpoints);
	void UpdateLaps(int CurrentLap = 0, int MaxLaps = 0);
	void UpdateCurrentLapTime(float NewCurrentLapTime);
	void UpdatePreviousLap(LapData NewPreviousLapData);
	void UpdateCurrentGear(int NewCurrentGear);

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

	UPROPERTY(EditAnywhere, BluePrintReadWrite, meta = (BindWidget))
	class UTextBlock *CurrentGearText;

	UPROPERTY(EditAnywhere, BluePrintReadWrite, meta = (BindWidget))
	class UProgressBar *CurrentSpeedProgressBar;
};
