// Copyright 2023 Teyon. All Rights Reserved.

#pragma once

#include "Blueprint/UserWidget.h"
#include "CoreMinimal.h"

#include "CarCustomizationWidget.generated.h"
/**
 *
 */
UCLASS()
class PRAKTYKI_API UCarCustomizationWidget : public UUserWidget {
	GENERATED_BODY()
public:
	UCarCustomizationWidget(const FObjectInitializer &ObjectInitializer);

	virtual void NativeConstruct() override;

	UTexture2D *ColorsTexture;

	UPROPERTY(EditAnywhere, BluePrintReadWrite, meta = (BindWidget))
	class UComboBoxString *CurrentCustomizationComboBoxString;

	UPROPERTY(EditAnywhere, BluePrintReadWrite, meta = (BindWidget))
	class UImage *ColorsImage;

	UPROPERTY(EditAnywhere, BluePrintReadWrite, meta = (BindWidget))
	class UImage *HoodColorImage;

	UPROPERTY(EditAnywhere, BluePrintReadWrite, meta = (BindWidget))
	class UImage *SpoilerColorImage;

	UPROPERTY(EditAnywhere, BluePrintReadWrite, meta = (BindWidget))
	class UImage *LeftDoorColorImage;

	UPROPERTY(EditAnywhere, BluePrintReadWrite, meta = (BindWidget))
	class UImage *RightDoorColorImage;
};
