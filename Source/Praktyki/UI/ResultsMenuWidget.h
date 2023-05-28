// Copyright 2023 Teyon. All Rights Reserved.

#pragma once

#include "../Gameplay/LapData.h"
#include "Blueprint/UserWidget.h"
#include "Components/RichTextBlock.h"
#include "CoreMinimal.h"
#include "Runtime/UMG/Public/UMG.h"

#include "ResultsMenuWidget.generated.h"

/**
 *
 */
UCLASS()
class PRAKTYKI_API UResultsMenuWidget : public UUserWidget {
	GENERATED_BODY()
public:
	UResultsMenuWidget(const FObjectInitializer &ObjectInitializer);

	virtual void NativeConstruct() override;

	UFUNCTION()
	void OpenMainMenu();

	UFUNCTION()
	void RestartGame();

	void UpdateBestLap(LapData NewBestLapData);
	void UpdateBestLap();

	UPROPERTY(EditAnywhere, BluePrintReadWrite, meta = (BindWidget))
	class UButton *MainMenuButton;

	UPROPERTY(EditAnywhere, BluePrintReadWrite, meta = (BindWidget))
	class UButton *RestartGameButton;

	UPROPERTY(EditAnywhere, BluePrintReadWrite, meta = (BindWidget))
	class URichTextBlock *BestLapText;
};
