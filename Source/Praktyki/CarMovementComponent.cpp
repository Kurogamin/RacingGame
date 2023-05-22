// Copyright 2023 Teyon. All Rights Reserved.


#include "CarMovementComponent.h"

// Sets default values for this component's properties
UCarMovementComponent::UCarMovementComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

}


// Called when the game starts
void UCarMovementComponent::BeginPlay()
{
	Super::BeginPlay();

	auto Owner = GetOwner();

	if (Owner)
	{
		auto component = Owner->GetComponentsByTag(UStaticMeshComponent::StaticClass(), FName("FL"));
		if (component.Num() != 0)
		{
			FrontLeftWheel = Cast<UStaticMeshComponent>(component[0]);
		}
		else
		{
			UE_LOG(LogTemp, Error, TEXT("FL not found"));
		}
	}
	
}


// Called every frame
void UCarMovementComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (FrontLeftWheel)
	{
		FrontLeftWheel->AddLocalRotation(FRotator(0, 0, 1));
	}
}

