// Copyright 2023 Teyon. All Rights Reserved.

#pragma once
#include "../Gameplay/LapData.h"
#include "Blueprint/UserWidget.h"
#include "CoreMinimal.h"

#include "MainMenuWidget.generated.h"

class UButton;
class UComboBoxString;
class URichTextBlock;
class USlider;
class UImage;
class UTexture2D;

/**
 *
 */
UCLASS() class PRAKTYKI_API UMainMenuWidget : public UUserWidget {
	GENERATED_BODY()
private:
	int NumberOfSeconds = 60;
	int NumberOfLaps = 1;

	void UpdateGameInstance();
	bool MultiLap = false;

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

	UFUNCTION()
	void LoadCarCustomization();

	UPROPERTY(EditAnywhere, BluePrintReadWrite, meta = (BindWidget))
	class UButton *StartGameButton;

	UPROPERTY(EditAnywhere, BluePrintReadWrite, meta = (BindWidget))
	class UButton *QuitGameButton;

	UPROPERTY(EditAnywhere, BluePrintReadWrite, meta = (BindWidget))
	class UButton *CarCustomizationButton;

	UPROPERTY(EditAnywhere, BluePrintReadWrite, meta = (BindWidget))
	class USlider *GameTimeSlider;

	UPROPERTY(EditAnywhere, BluePrintReadWrite, meta = (BindWidget))
	class USlider *GameLapsSlider;

	UPROPERTY(EditAnywhere, BluePrintReadWrite, meta = (BindWidget))
	class URichTextBlock *SliderText;

	UPROPERTY(EditAnywhere, BluePrintReadWrite, meta = (BindWidget))
	class UComboBoxString *GameTypeComboBox;
};
