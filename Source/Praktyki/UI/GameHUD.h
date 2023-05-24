// Copyright 2023 Teyon. All Rights Reserved.

#pragma once

#include "CarWidget.h"
#include "Components/WidgetComponent.h"
#include "CoreMinimal.h"
#include "GameFramework/HUD.h"

#include "GameHUD.generated.h"

/**
 *
 */
UCLASS()
class PRAKTYKI_API AGameHUD : public AHUD {
	GENERATED_BODY()
public:
	AGameHUD();

	virtual void DrawHUD() override;

	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	void UpdateCurrentSpeed(float NewCurrentSpeed);

	UPROPERTY(EditDefaultsOnly, Category = "Widgets")
	TSubclassOf<UCarWidget> CarWidgetClass;

private:
	UCarWidget *CarWidget;
};
