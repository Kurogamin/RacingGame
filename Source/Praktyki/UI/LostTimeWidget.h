// Copyright 2023 Teyon. All Rights Reserved.

#pragma once

#include "Blueprint/UserWidget.h"
#include "CoreMinimal.h"
#include "Runtime/UMG/Public/UMG.h"

#include "LostTimeWidget.generated.h"

/**
 *
 */
UCLASS()
class PRAKTYKI_API ULostTimeWidget : public UUserWidget {
	GENERATED_BODY()
private:
	float LostTime = 0.0f;

public:
	ULostTimeWidget(const FObjectInitializer &ObjectInitializer);

	virtual void NativeConstruct() override;

	void AddLostTime(float AddValue);

	UPROPERTY(EditAnywhere, BluePrintReadWrite, meta = (BindWidget))
	class UTextBlock *LostTimeText;
};
