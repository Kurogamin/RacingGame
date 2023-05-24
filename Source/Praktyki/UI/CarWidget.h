// Copyright 2023 Teyon. All Rights Reserved.

#pragma once

#include "Blueprint/UserWidget.h"
#include "CoreMinimal.h"
#include "Runtime/UMG/Public/UMG.h"

#include "CarWidget.generated.h"
/**
 *
 */
UCLASS()
class PRAKTYKI_API UCarWidget : public UUserWidget {
	GENERATED_BODY()
private:
	float CurrentSpeed = 0.0f;

public:
	UCarWidget(const FObjectInitializer &ObjectInitializer);

	virtual void NativeConstruct() override;

	void SetCurrentSpeed(float NewCurrentSpeed);

	UPROPERTY(EditAnywhere, BluePrintReadWrite, meta = (BindWidget))
	class UTextBlock *CurrentSpeedText;
};
