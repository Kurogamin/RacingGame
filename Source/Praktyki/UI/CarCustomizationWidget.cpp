// Copyright 2023 Teyon. All Rights Reserved.

#include "CarCustomizationWidget.h"
#include "../GameModes/CarCustomizationGameModeBase.h"
#include "Components/CheckBox.h"
#include "Components/ComboBoxString.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "Kismet/GameplayStatics.h"

UCarCustomizationWidget::UCarCustomizationWidget(const FObjectInitializer &ObjectInitializer) :
		Super(ObjectInitializer) {
}

void UCarCustomizationWidget::NativeConstruct() {
	Super::NativeConstruct();

	GameMode = Cast<ACarCustomizationGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()));
	CustomCarPart.Init(false, 4);

	ColorsTexture = Cast<UTexture2D>(
			StaticLoadObject(UTexture2D::StaticClass(), nullptr, TEXT("/Game/UI/Images/Colors")));

	HoodMaterial = Cast<UMaterial>(StaticLoadObject(
			UMaterial::StaticClass(), nullptr, TEXT("/Game/Materials/HoodMaterial")));

	SpoilerMaterial = Cast<UMaterial>(StaticLoadObject(
			UMaterial::StaticClass(), nullptr, TEXT("/Game/Materials/SpoilerMaterial")));

	LeftDoorMaterial = Cast<UMaterial>(StaticLoadObject(
			UMaterial::StaticClass(), nullptr, TEXT("/Game/Materials/LeftDoorMaterial")));

	RightDoorMaterial = Cast<UMaterial>(StaticLoadObject(
			UMaterial::StaticClass(), nullptr, TEXT("/Game/Materials/RightDoorMaterial")));

	if (CurrentCustomizationComboBoxString) {
		CurrentCustomizationComboBoxString->OnSelectionChanged.AddDynamic(
				this, &UCarCustomizationWidget::OnCarPartChanged);
	}
}

void UCarCustomizationWidget::OnCarPartChanged(FString SelectedItem, ESelectInfo::Type SelectInfo) {
	UE_LOG(LogTemp, Warning, TEXT("SELECTED ITEM: %s"), *SelectedItem);
	if (SelectedItem == "Overview") {
		CustomCheckBox->SetVisibility(ESlateVisibility::Hidden);
		CustomText->SetVisibility(ESlateVisibility::Hidden);
		GameMode->ChangeCameraPosition(4);
		return;
	}
	CustomCheckBox->SetVisibility(ESlateVisibility::Visible);
	CustomText->SetVisibility(ESlateVisibility::Visible);

	if (SelectedItem == "Hood") {
		CustomCheckBox->SetIsChecked(CustomCarPart[0]);
		GameMode->ChangeCameraPosition(0);
		CurrentCarPart = CarPart::Hood;
	} else if (SelectedItem == "Spoiler") {
		CustomCheckBox->SetIsChecked(CustomCarPart[1]);
		GameMode->ChangeCameraPosition(1);
		CurrentCarPart = CarPart::Spoiler;
	} else if (SelectedItem == "LeftDoor") {
		CustomCheckBox->SetIsChecked(CustomCarPart[2]);
		GameMode->ChangeCameraPosition(2);
		CurrentCarPart = CarPart::LeftDoor;
	} else if (SelectedItem == "RightDoor") {
		CustomCheckBox->SetIsChecked(CustomCarPart[3]);
		GameMode->ChangeCameraPosition(3);
		CurrentCarPart = CarPart::RightDoor;
	}
}
