// Copyright 2023 Teyon. All Rights Reserved.

#pragma once

#include "CarWidget.h"
#include "Components/WidgetComponent.h"
#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "MainMenuWidget.h"
#include "ResultsMenuWidget.h"

#include "GameHUD.generated.h"

/**
 *
 */
UCLASS()
class PRAKTYKI_API AGameHUD : public AHUD {
	GENERATED_BODY()
private:
public:
	AGameHUD();

	virtual void DrawHUD() override;
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	void UpdateCurrentSpeed(float NewCurrentSpeed);
	void UpdateLostTime(float NewLostTime);
	void UpdateCheckpoints(int CurrentCheckpoints = 0, int MaxCheckpoints = 0);
	void UpdateLaps(int CurrentLap = 0, int MaxLaps = 0);
	void UpdateCurrentLapTime(float NewCurrentLapTime);
	void UpdatePreviousLap(float PreviousLapTime, float PreviousLapLostTime);

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
