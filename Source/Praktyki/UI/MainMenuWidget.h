// Copyright 2023 Teyon. All Rights Reserved.

#pragma once

#include "Blueprint/UserWidget.h"
#include "CoreMinimal.h"
#include "Runtime/UMG/Public/UMG.h"

#include "MainMenuWidget.generated.h"
/**
 *
 */
UCLASS()
class PRAKTYKI_API UMainMenuWidget : public UUserWidget {
	GENERATED_BODY()
public:
	UMainMenuWidget(const FObjectInitializer &ObjectInitializer);

	virtual void NativeConstruct() override;

	UFUNCTION()
	void OpenRaceLevel();

	UFUNCTION()
	void QuitGame();

	UPROPERTY(EditAnywhere, BluePrintReadWrite, meta = (BindWidget))
	class UButton *StartGameButton;

	UPROPERTY(EditAnywhere, BluePrintReadWrite, meta = (BindWidget))
	class UButton *QuitGameButton;
};
