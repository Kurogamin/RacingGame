// Copyright 2023 Teyon. All Rights Reserved.

#pragma once

#include "Blueprint/UserWidget.h"
#include "CoreMinimal.h"

#include "CarCustomizationWidget.generated.h"
/**
 *
 */

class UMaterial;
class ACarCustomizationGameModeBase;

UENUM()
enum class CarPart { Overview, Spoiler, LeftDoor, RightDoor, Hood };

UCLASS()
class PRAKTYKI_API UCarCustomizationWidget : public UUserWidget {
	GENERATED_BODY()
private:
	TArray<bool> CustomCarPart;
	CarPart CurrentCarPart = CarPart::Overview;

	UMaterial *HoodMaterial;
	UMaterial *SpoilerMaterial;
	UMaterial *LeftDoorMaterial;
	UMaterial *RightDoorMaterial;

	ACarCustomizationGameModeBase *GameMode;

public:
	UCarCustomizationWidget(const FObjectInitializer &ObjectInitializer);

	virtual void NativeConstruct() override;

	UTexture2D *ColorsTexture;

	UFUNCTION()
	void OnCarPartChanged(FString SelectedItem, ESelectInfo::Type SelectInfo);

	UPROPERTY(EditAnywhere, BluePrintReadWrite, meta = (BindWidget))
	class UComboBoxString *CurrentCustomizationComboBoxString;

	UPROPERTY(EditAnywhere, BluePrintReadWrite, meta = (BindWidget))
	class UImage *ColorsImage;

	UPROPERTY(EditAnywhere, BluePrintReadWrite, meta = (BindWidget))
	class UImage *HoodColorImage;

	UPROPERTY(EditAnywhere, BluePrintReadWrite, meta = (BindWidget))
	class UTextBlock *TextBlockHood;

	UPROPERTY(EditAnywhere, BluePrintReadWrite, meta = (BindWidget))
	class UImage *SpoilerColorImage;

	UPROPERTY(EditAnywhere, BluePrintReadWrite, meta = (BindWidget))
	class UTextBlock *TextBlockSpoiler;

	UPROPERTY(EditAnywhere, BluePrintReadWrite, meta = (BindWidget))
	class UImage *LeftDoorColorImage;

	UPROPERTY(EditAnywhere, BluePrintReadWrite, meta = (BindWidget))
	class UTextBlock *TextBlockLeftDoor;

	UPROPERTY(EditAnywhere, BluePrintReadWrite, meta = (BindWidget))
	class UImage *RightDoorColorImage;

	UPROPERTY(EditAnywhere, BluePrintReadWrite, meta = (BindWidget))
	class UTextBlock *TextBlockRightDoor;

	UPROPERTY(EditAnywhere, BluePrintReadWrite, meta = (BindWidget))
	class UCheckBox *CustomCheckBox;

	UPROPERTY(EditAnywhere, BluePrintReadWrite, meta = (BindWidget))
	class UTextBlock *CustomText;
};
