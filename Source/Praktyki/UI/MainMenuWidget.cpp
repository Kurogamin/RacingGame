// Copyright 2023 Teyon. All Rights Reserved.

#include "MainMenuWidget.h"
#include "../GameModes/RacingGameInstance.h"
#include "Components/ComboBoxString.h"
#include "Components/Image.h"
#include "Components/RichTextBlock.h"
#include "Components/Slider.h"
#include "Runtime/UMG/Public/UMG.h"

UMainMenuWidget::UMainMenuWidget(const FObjectInitializer &ObjectInitializer) :
		Super(ObjectInitializer) {
}

void UMainMenuWidget::NativeConstruct() {
	Super::NativeConstruct();

	ColorsTexture = Cast<UTexture2D>(
			StaticLoadObject(UTexture2D::StaticClass(), nullptr, TEXT("/Game/UI/Images/Colors")));

	if (StartGameButton) {
		StartGameButton->OnClicked.AddDynamic(this, &UMainMenuWidget::OpenRaceLevel);
	}

	if (QuitGameButton) {
		QuitGameButton->OnClicked.AddDynamic(this, &UMainMenuWidget::QuitGame);
	}

	if (GameTimeSlider) {
		GameTimeSlider->OnValueChanged.AddDynamic(this, &UMainMenuWidget::OnGameTimeSliderChanged);
	}

	if (GameLapsSlider) {
		GameLapsSlider->OnValueChanged.AddDynamic(this, &UMainMenuWidget::OnGameLapsSliderChanged);
	}

	if (GameTypeComboBox) {
		GameTypeComboBox->OnSelectionChanged.AddDynamic(this, &UMainMenuWidget::OnGameTypeChanged);
	}

	if (ColorsImage) {
		ColorsImage->OnMouseButtonDownEvent.BindUFunction(this, FName("OnLeftMouseButtonPressed"));
	}

	if (CarCustomizationButton) {
		CarCustomizationButton->OnClicked.AddDynamic(
				this, &UMainMenuWidget::SwitchColorsImageVisibility);
	}
}

void UMainMenuWidget::OpenRaceLevel() {
	auto World = GetWorld();
	URacingGameInstance *GameInstance =
			Cast<URacingGameInstance>(UGameplayStatics::GetGameInstance(World));
	GameInstance->SetNumberOfLaps(NumberOfLaps);
	GameInstance->SetNumberOfSeconds(NumberOfSeconds);

	UGameplayStatics::OpenLevel(GetWorld(), FName("TestMap"));
}

void UMainMenuWidget::QuitGame() {
	UKismetSystemLibrary::QuitGame(GetWorld(), GetOwningPlayer(), EQuitPreference::Quit, false);
}

void UMainMenuWidget::OnGameTimeSliderChanged(float Value) {
	NumberOfSeconds = GameTimeSlider->GetValue();
	NumberOfSeconds = FMath::RoundToFloat(NumberOfSeconds / 10) * 10;
}

void UMainMenuWidget::OnGameLapsSliderChanged(float Value) {
	NumberOfLaps = GameLapsSlider->GetValue();
}

void UMainMenuWidget::OnGameTypeChanged(FString SelectedItem, ESelectInfo::Type SelectInfo) {
	if (GameTypeComboBox && GameTimeSlider && GameLapsSlider && SliderText) {
		if (SelectedItem == "Single Lap") {
			GameTimeSlider->SetVisibility(ESlateVisibility::Visible);
			GameLapsSlider->SetVisibility(ESlateVisibility::Hidden);
		} else if (SelectedItem == "Multi Lap") {
			if (NumberOfLaps == 1) {
				NumberOfLaps = 2;
			}
			GameTimeSlider->SetVisibility(ESlateVisibility::Hidden);
			GameLapsSlider->SetVisibility(ESlateVisibility::Visible);
		}
	}
}

void UMainMenuWidget::NativeTick(const FGeometry &MyGeometry, float DeltaTime) {
	Super::Tick(MyGeometry, DeltaTime);

	if (SliderText) {
		if (GameTypeComboBox->GetSelectedIndex() == 0) {
			SliderText->SetText(FText::FromString(
					"Game length: " + FString::FromInt(NumberOfSeconds) + " seconds"));
		} else if (GameTypeComboBox->GetSelectedIndex() == 1) {
			SliderText->SetText(
					FText::FromString("Number of laps: " + FString::FromInt(NumberOfLaps)));
		}
	}
}

void UMainMenuWidget::SwitchColorsImageVisibility() {
	if (ColorsImage) {
		if (ColorsImage->IsVisible()) {
			ColorsImage->SetVisibility(ESlateVisibility::Hidden);
		} else {
			ColorsImage->SetVisibility(ESlateVisibility::Visible);
		}
	}
}

void UMainMenuWidget::OnLeftMouseButtonPressed(FGeometry MyGeometry, FPointerEvent MouseEvent) {
	if (MouseEvent.GetEffectingButton() == EKeys::LeftMouseButton) {
		FVector2D LocalCursorPos = MyGeometry.AbsoluteToLocal(MouseEvent.GetScreenSpacePosition());

		if (ColorsImage && ColorsTexture && CurrentColor) {
			if (!ColorsImage->IsHovered() || !ColorsImage->IsVisible()) {
				return;
			}
			// Get the texture size
			int TextureWidth = ColorsTexture->GetSurfaceWidth();
			int TextureHeight = ColorsTexture->GetSurfaceHeight();

			// Calculate the UV coordinates
			float U = LocalCursorPos.X / MyGeometry.GetLocalSize().X;
			float V = LocalCursorPos.Y / MyGeometry.GetLocalSize().Y;

			int PixelX = FMath::FloorToInt(U * TextureWidth);
			int PixelY = FMath::FloorToInt(V * TextureHeight);

			FTexture2DMipMap *ColorsTextureMipMap = &ColorsTexture->PlatformData->Mips[0];
			FByteBulkData *RawImageData = &ColorsTextureMipMap->BulkData;
			FColor *FormatedImageData = static_cast<FColor *>(RawImageData->Lock(LOCK_READ_ONLY));

			FColor PixelColor = FormatedImageData[PixelY * TextureWidth + PixelX];
			RawImageData->Unlock();

			// Set the color of the second image
			CurrentColor->SetColorAndOpacity(FLinearColor(PixelColor));
		}
	}
}