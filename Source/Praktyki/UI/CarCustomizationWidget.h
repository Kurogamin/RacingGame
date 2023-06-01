// Copyright 2023 Teyon. All Rights Reserved.

#pragma once

#include "Blueprint/UserWidget.h"
#include "CoreMinimal.h"

#include "CarCustomizationWidget.generated.h"
/**
 *
 */

class UImage;
class ACarCustomizationGameModeBase;
class UTexture2D;
class UButton;

UENUM()
enum class CarPart { Hood, Spoiler, LeftDoor, RightDoor, Overview };

UCLASS()
class PRAKTYKI_API UCarCustomizationWidget : public UUserWidget {
	GENERATED_BODY()
private:
	TArray<bool> CustomCarPart;
	CarPart CurrentCarPart = CarPart::Overview;

	ACarCustomizationGameModeBase *GameMode = nullptr;

	UImage *CurrentPartColorImage = nullptr;
	UTexture2D *ColorsTexture = nullptr;

public:
	UCarCustomizationWidget(const FObjectInitializer &ObjectInitializer);

	virtual void NativeConstruct() override;

	UFUNCTION()
	void OnCarPartChanged(FString SelectedItem, ESelectInfo::Type SelectInfo);

	UFUNCTION()
	void OnCustomCheckboxChanged(bool NewValue);

	UFUNCTION()
	void OnLeftMouseButtonPressed(FGeometry MyGeometry, FPointerEvent MouseEvent);

	UFUNCTION()
	void StartGame();

	UFUNCTION()
	void MainMenu();

	UPROPERTY(EditAnywhere, BluePrintReadWrite, meta = (BindWidget))
	class UComboBoxString *CurrentCustomizationComboBoxString;

	UPROPERTY(EditAnywhere, BluePrintReadWrite, meta = (BindWidget))
	class UImage *ColorsImage;

	UPROPERTY(EditAnywhere, BluePrintReadWrite, meta = (BindWidget))
	class UImage *HoodColorImage;

	UPROPERTY(EditAnywhere, BluePrintReadWrite, meta = (BindWidget))
	class UTextBlock *HoodTextBlock;

	UPROPERTY(EditAnywhere, BluePrintReadWrite, meta = (BindWidget))
	class UImage *SpoilerColorImage;

	UPROPERTY(EditAnywhere, BluePrintReadWrite, meta = (BindWidget))
	class UTextBlock *SpoilerTextBlock;

	UPROPERTY(EditAnywhere, BluePrintReadWrite, meta = (BindWidget))
	class UImage *LeftDoorColorImage;

	UPROPERTY(EditAnywhere, BluePrintReadWrite, meta = (BindWidget))
	class UTextBlock *LeftDoorTextBlock;

	UPROPERTY(EditAnywhere, BluePrintReadWrite, meta = (BindWidget))
	class UImage *RightDoorColorImage;

	UPROPERTY(EditAnywhere, BluePrintReadWrite, meta = (BindWidget))
	class UTextBlock *RightDoorTextBlock;

	UPROPERTY(EditAnywhere, BluePrintReadWrite, meta = (BindWidget))
	class UCheckBox *CustomCheckBox;

	UPROPERTY(EditAnywhere, BluePrintReadWrite, meta = (BindWidget))
	class UTextBlock *CustomText;

	UPROPERTY(EditAnywhere, BluePrintReadWrite, meta = (BindWidget))
	class UButton *StartGameButton;

	UPROPERTY(EditAnywhere, BluePrintReadWrite, meta = (BindWidget))
	class UButton *MainMenuButton;
};
