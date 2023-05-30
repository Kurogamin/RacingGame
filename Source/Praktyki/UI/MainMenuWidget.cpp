// Copyright 2023 Teyon. All Rights Reserved.

#include "MainMenuWidget.h"
#include "../GameModes/RacingGameInstance.h"
#include "Components/ComboBoxString.h"
#include "Components/RichTextBlock.h"
#include "Components/Slider.h"
#include "Runtime/UMG/Public/UMG.h"

UMainMenuWidget::UMainMenuWidget(const FObjectInitializer &ObjectInitializer) :
		Super(ObjectInitializer) {
}

void UMainMenuWidget::NativeConstruct() {
	Super::NativeConstruct();

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
