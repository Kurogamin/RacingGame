// Copyright 2023 Teyon. All Rights Reserved.

#include "MainMenuWidget.h"

UMainMenuWidget::UMainMenuWidget(const FObjectInitializer &ObjectInitializer) : Super(ObjectInitializer) {
}

void UMainMenuWidget::NativeConstruct() {
	Super::NativeConstruct();

	if (StartGameButton) {
		StartGameButton->OnClicked.AddDynamic(this, &UMainMenuWidget::OpenRaceLevel);
	}

	if (QuitGameButton) {
		QuitGameButton->OnClicked.AddDynamic(this, &UMainMenuWidget::QuitGame);
	}
}

void UMainMenuWidget::OpenRaceLevel() {
	UGameplayStatics::OpenLevel(GetWorld(), FName("TestMap"));
	UE_LOG(LogTemp, Warning, TEXT("OpenRaceLevel"));
}

void UMainMenuWidget::QuitGame() {
	UKismetSystemLibrary::QuitGame(GetWorld(), GetOwningPlayer(), EQuitPreference::Quit, false);
	UE_LOG(LogTemp, Warning, TEXT("QuitGame"));
}
