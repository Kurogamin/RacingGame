// Copyright 2023 Teyon. All Rights Reserved.

#pragma once

#include "Blueprint/UserWidget.h"
#include "Components/ComboBoxString.h"
#include "Components/RichTextBlock.h"
#include "Components/Slider.h"
#include "CoreMinimal.h"
#include "Runtime/UMG/Public/UMG.h"

#include "MainMenuWidget.generated.h"
/**
 *
 */
UCLASS()
class PRAKTYKI_API UMainMenuWidget : public UUserWidget {
	GENERATED_BODY()
private:
	int NumberOfSeconds = 60;
	int NumberOfLaps = 1;

protected:
	virtual void NativeTick(const FGeometry &MyGeometry, float DeltaTime) override;

public:
	UMainMenuWidget(const FObjectInitializer &ObjectInitializer);

	virtual void NativeConstruct() override;

	UFUNCTION()
	void OpenRaceLevel();

	UFUNCTION()
	void QuitGame();

	UFUNCTION()
	void OnGameTimeSliderChanged(float Value);

	UFUNCTION()
	void OnGameLapsSliderChanged(float Value);

	UFUNCTION()
	void OnGameTypeChanged(FString SelectedItem, ESelectInfo::Type SelectInfo);

	UPROPERTY(EditAnywhere, BluePrintReadWrite, meta = (BindWidget))
	class UButton *StartGameButton;

	UPROPERTY(EditAnywhere, BluePrintReadWrite, meta = (BindWidget))
	class UButton *QuitGameButton;

	UPROPERTY(EditAnywhere, BluePrintReadWrite, meta = (BindWidget))
	class USlider *GameTimeSlider;

	UPROPERTY(EditAnywhere, BluePrintReadWrite, meta = (BindWidget))
	class USlider *GameLapsSlider;

	UPROPERTY(EditAnywhere, BluePrintReadWrite, meta = (BindWidget))
	class URichTextBlock *SliderText;

	UPROPERTY(EditAnywhere, BluePrintReadWrite, meta = (BindWidget))
	class UComboBoxString *GameTypeComboBox;
};
