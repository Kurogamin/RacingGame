// Copyright 2023 Teyon. All Rights Reserved.

#include "CarCustomizationWidget.h"
#include "../GameModes/CarCustomizationGameModeBase.h"
#include "../GameModes/RacingGameInstance.h"
#include "Components/Button.h"
#include "Components/CheckBox.h"
#include "Components/ComboBoxString.h"
#include "Components/Image.h"
#include "Components/StaticMeshComponent.h"
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

	if (CurrentCustomizationComboBoxString) {
		CurrentCustomizationComboBoxString->OnSelectionChanged.AddDynamic(
				this, &UCarCustomizationWidget::OnCarPartChanged);
	}

	if (CustomCheckBox) {
		CustomCheckBox->OnCheckStateChanged.AddDynamic(
				this, &UCarCustomizationWidget::OnCustomCheckboxChanged);
	}

	if (ColorsImage) {
		ColorsImage->OnMouseButtonDownEvent.BindUFunction(this, FName("OnLeftMouseButtonPressed"));
	}

	if (StartGameButton) {
		StartGameButton->OnClicked.AddDynamic(this, &UCarCustomizationWidget::StartGame);
	}

	if (MainMenuButton) {
		MainMenuButton->OnClicked.AddDynamic(this, &UCarCustomizationWidget::MainMenu);
	}

	ColorsTexture = Cast<UTexture2D>(
			StaticLoadObject(UTexture2D::StaticClass(), nullptr, TEXT("/Game/UI/Images/Colors")));
}

void UCarCustomizationWidget::OnCarPartChanged(FString SelectedItem, ESelectInfo::Type SelectInfo) {
	if (SelectedItem == "Overview") {
		CustomCheckBox->SetVisibility(ESlateVisibility::Hidden);
		CustomText->SetVisibility(ESlateVisibility::Hidden);
		ColorsImage->SetVisibility(ESlateVisibility::Hidden);
		GameMode->ChangeCameraPosition(4);
		CurrentPartColorImage = nullptr;
		return;
	}
	CustomCheckBox->SetVisibility(ESlateVisibility::Visible);
	CustomText->SetVisibility(ESlateVisibility::Visible);
	int CurrentPartIndex = 0;

	if (SelectedItem == "Hood") {
		CurrentPartIndex = 0;
		CurrentCarPart = CarPart::Hood;
		CurrentPartColorImage = HoodColorImage;
	} else if (SelectedItem == "Spoiler") {
		CurrentPartIndex = 1;
		CurrentCarPart = CarPart::Spoiler;
		CurrentPartColorImage = SpoilerColorImage;
	} else if (SelectedItem == "LeftDoor") {
		CurrentPartIndex = 2;
		CurrentCarPart = CarPart::LeftDoor;
		CurrentPartColorImage = LeftDoorColorImage;
	} else if (SelectedItem == "RightDoor") {
		CurrentPartIndex = 3;
		CurrentCarPart = CarPart::RightDoor;
		CurrentPartColorImage = RightDoorColorImage;
	}

	ESlateVisibility ColorsVisibility =
			CustomCarPart[CurrentPartIndex] ? ESlateVisibility::Visible : ESlateVisibility::Hidden;
	ColorsImage->SetVisibility(ColorsVisibility);
	GameMode->ChangeCameraPosition(CurrentPartIndex);
	bool CustomPart = CustomCarPart[CurrentPartIndex];
	CustomCheckBox->SetIsChecked(CustomPart);
}

void UCarCustomizationWidget::OnCustomCheckboxChanged(bool NewValue) {
	ESlateVisibility NewVisibility =
			NewValue ? ESlateVisibility::Visible : ESlateVisibility::Hidden;
	switch (CurrentCarPart) {
		case CarPart::Hood:
			HoodColorImage->SetVisibility(NewVisibility);
			HoodTextBlock->SetVisibility(NewVisibility);
			break;
		case CarPart::Spoiler:
			SpoilerColorImage->SetVisibility(NewVisibility);
			SpoilerTextBlock->SetVisibility(NewVisibility);
			break;
		case CarPart::LeftDoor:
			LeftDoorColorImage->SetVisibility(NewVisibility);
			LeftDoorTextBlock->SetVisibility(NewVisibility);
			break;
		case CarPart::RightDoor:
			RightDoorColorImage->SetVisibility(NewVisibility);
			RightDoorTextBlock->SetVisibility(NewVisibility);
			break;
	}
	CustomCarPart[(int)CurrentCarPart] = NewValue;
	ColorsImage->SetVisibility(NewVisibility);
	GameMode->SetCustomPart((int)CurrentCarPart, NewValue);
}

void UCarCustomizationWidget::OnLeftMouseButtonPressed(
		FGeometry MyGeometry, FPointerEvent MouseEvent) {
	if (MouseEvent.GetEffectingButton() == EKeys::LeftMouseButton) {
		FVector2D LocalCursorPos = MyGeometry.AbsoluteToLocal(MouseEvent.GetScreenSpacePosition());

		if (ColorsImage && ColorsTexture && CurrentPartColorImage) {
			if (!ColorsImage->IsHovered() || !ColorsImage->IsVisible()) {
				return;
			}

			int TextureWidth = ColorsTexture->GetSurfaceWidth();
			int TextureHeight = ColorsTexture->GetSurfaceHeight();

			float U = LocalCursorPos.X / MyGeometry.GetLocalSize().X;
			float V = LocalCursorPos.Y / MyGeometry.GetLocalSize().Y;

			int PixelX = FMath::FloorToInt(U * TextureWidth);
			int PixelY = FMath::FloorToInt(V * TextureHeight);

			FTexture2DMipMap *ColorsTextureMipMap = &ColorsTexture->GetPlatformData()->Mips[0];
			FByteBulkData *RawImageData = &ColorsTextureMipMap->BulkData;
			FColor *FormatedImageData = static_cast<FColor *>(RawImageData->Lock(LOCK_READ_ONLY));

			FLinearColor PixelColor = FormatedImageData[PixelY * TextureWidth + PixelX];
			RawImageData->Unlock();

			CurrentPartColorImage->SetColorAndOpacity(FLinearColor(PixelColor));
			GameMode->SetMaterialColor((int)CurrentCarPart, PixelColor);

			URacingGameInstance *GameInstance = Cast<URacingGameInstance>(GetGameInstance());
			GameInstance->SetCustomMaterialColor((int)CurrentCarPart, PixelColor);
		}
	}
}

void UCarCustomizationWidget::StartGame() {
	auto GameInstance = Cast<URacingGameInstance>(GetGameInstance());
	GameInstance->SetCustomParts(CustomCarPart);
	UGameplayStatics::OpenLevel(GetWorld(), "TestMap");
}

void UCarCustomizationWidget::MainMenu() {
	auto GameInstance = Cast<URacingGameInstance>(GetGameInstance());
	GameInstance->SetCustomParts(CustomCarPart);
	UGameplayStatics::OpenLevel(GetWorld(), "MainMenuMap");
}