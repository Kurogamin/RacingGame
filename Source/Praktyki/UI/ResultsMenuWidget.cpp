// Copyright 2023 Teyon. All Rights Reserved.

#include "ResultsMenuWidget.h"
#include "Components/RichTextBlock.h"
#include "Runtime/UMG/Public/UMG.h"

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
		FString BestLapString = NewBestLapData.ToRichString() + FString("\n");
		NewBestLapData.CheckpointTimes.Sort();
		int i = 0;
		for (auto Checkpoint : NewBestLapData.CheckpointTimes) {
			i++;
			BestLapString += FString::Printf(TEXT("Checkpoint %i: "), i) +
					LapData::FloatToRoundedString(Checkpoint) + FString("\n");
		}
		BestLapText->SetText(FText::FromString(BestLapString));
	}
}

void UResultsMenuWidget::UpdateBestLap() {
	if (BestLapText) {
		BestLapText->SetText(FText::FromString("No best lap"));
	}
}
