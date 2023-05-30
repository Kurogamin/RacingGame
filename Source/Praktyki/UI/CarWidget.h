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

	void UpdateCurrentSpeed(float NewCurrentSpeed, int NewCurrentGear, float NewPercent);
	void UpdateCheckpoints(int CurrentCheckpoints, int MaxCheckpoints);
	void UpdateLaps(int CurrentLap = 0, int MaxLaps = 0);
	void UpdateCurrentLapTime(float NewLapTime, float NewLapLostTime);
	void UpdateBestLapTime(LapData NewBestLapData);
	void UpdateCurrentCheckpoint(float NewCurrentCheckpoint);

	UPROPERTY(EditAnywhere, BluePrintReadWrite, meta = (BindWidget))
	class UTextBlock *CurrentSpeedText;

	UPROPERTY(EditAnywhere, BluePrintReadWrite, meta = (BindWidget))
	class UTextBlock *CurrentGearText;

	UPROPERTY(EditAnywhere, BluePrintReadWrite, meta = (BindWidget))
	class UTextBlock *CheckpointsText;

	UPROPERTY(EditAnywhere, BluePrintReadWrite, meta = (BindWidget))
	class UTextBlock *LapsText;

	UPROPERTY(EditAnywhere, BluePrintReadWrite, meta = (BindWidget))
	class UTextBlock *CurrentCheckpointText;

	UPROPERTY(EditAnywhere, BluePrintReadWrite, meta = (BindWidget))
	class URichTextBlock *CurrentLapTimeText;

	UPROPERTY(EditAnywhere, BluePrintReadWrite, meta = (BindWidget))
	class URichTextBlock *BestLapTimeText;

	UPROPERTY(EditAnywhere, BluePrintReadWrite, meta = (BindWidget))
	class UProgressBar *CurrentSpeedProgressBar;
};
