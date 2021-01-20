// Fill out your copyright notice in the Description page of Project Settings.


#include "StaminaComponent.h"

// Sets default values for this component's properties
UStaminaComponent::UStaminaComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UStaminaComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...

}


// Called every frame
void UStaminaComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (isResting) {
		Resting(DeltaTime);
	}
}

void UStaminaComponent::AdjustStamina(float value)
{
	if ((staminaValue + value) > initialStaminaValue)
	{
		staminaValue = initialStaminaValue;
	}
	else
	{
		staminaValue += value;
	}

	if (canRun) {
		canRun = (staminaValue > 0);
	}
	else {
		canRun = (staminaValue == initialStaminaValue);
	}
}

bool UStaminaComponent::CanRun()
{
	return canRun;
}

void UStaminaComponent::StartResting()
{
	isResting = true;
}

void UStaminaComponent::Resting(float DeltaTime)
{
	AdjustStamina(regenerationValue * DeltaTime);
	isResting = (staminaValue == initialStaminaValue);
}

void UStaminaComponent::Fatique(float DeltaTime)
{
	AdjustStamina(fatiqueValue * DeltaTime);
}

