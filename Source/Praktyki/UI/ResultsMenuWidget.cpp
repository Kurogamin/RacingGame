// Copyright 2023 Teyon. All Rights Reserved.

#include "ResultsMenuWidget.h"

UResultsMenuWidget::UResultsMenuWidget(const FObjectInitializer &ObjectInitializer) :
		Super(ObjectInitializer) {
}

void UResultsMenuWidget::NativeConstruct() {
	Super::NativeConstruct();

	if (MainMenuButton) {
		MainMenuButton->OnClicked.AddDynamic(this, &UResultsMenuWidget::OpenMainMenu);
	}

	if (RestartGameButton) {
		RestartGameButton->OnClicked.AddDynamic(this, &UResultsMenuWidget::RestartGame);
	}
}

void UResultsMenuWidget::OpenMainMenu() {
	UGameplayStatics::OpenLevel(GetWorld(), FName("MainMenuMap"));
}

void UResultsMenuWidget::RestartGame() {
	UGameplayStatics::OpenLevel(GetWorld(), FName("TestMap"));
}

void UResultsMenuWidget::UpdateBestLap(LapData NewBestLapData) {
	if (BestLapText) {
		BestLapText->SetText(FText::FromString(NewBestLapData.ToRichString()));
	}
}

void UResultsMenuWidget::UpdateBestLap() {
	if (BestLapText) {
		BestLapText->SetText(FText::FromString("No best lap"));
	}
}
