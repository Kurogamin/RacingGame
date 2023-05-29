// Copyright 2023 Teyon. All Rights Reserved.

#pragma once

#include "Components/WidgetComponent.h"
#include "CoreMinimal.h"
#include "GameFramework/HUD.h"

#include "GameHUD.generated.h"

class UCarWidget;
class UMainMenuWidget;
class UResultsMenuWidget;
struct LapData;

/**
 *
 */
UCLASS()
class PRAKTYKI_API AGameHUD : public AHUD {
	GENERATED_BODY()
private:
	bool BestLapSet = false;

public:
	AGameHUD();

	virtual void DrawHUD() override;
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	void UpdateCurrentSpeed(float NewCurrentSpeed);
	void UpdateCurrentSpeedProgressBar(float NewPercent);
	void UpdateLostTime(float NewLostTime);
	void UpdateCheckpoints(int CurrentCheckpoints = 0, int MaxCheckpoints = 0);
	void UpdateLaps(int CurrentLap = 0, int MaxLaps = 0);
	void UpdateCurrentLapTime(float NewCurrentLapTime);
	void UpdatePreviousLap(LapData NewPreviousLapData);
	void UpdateCurrentGear(int NewCurrentGear);
	bool UpdateBestLap(LapData NewBestLapData);

	UPROPERTY(EditDefaultsOnly, Category = "Widgets")
	TSubclassOf<UCarWidget> CarWidgetClass;

	UPROPERTY(EditDefaultsOnly, Category = "Widgets")
	TSubclassOf<UMainMenuWidget> MainMenuWidgetClass;

	UPROPERTY(EditDefaultsOnly, Category = "Widgets")
	TSubclassOf<UResultsMenuWidget> ResultsMenuWidgetClass;

private:
	UCarWidget *CarWidget;
	UMainMenuWidget *MainMenuWidget;
	UResultsMenuWidget *ResultsMenuWidget;
};
