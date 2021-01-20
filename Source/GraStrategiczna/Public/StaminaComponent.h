// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "StaminaComponent.generated.h"


UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class GRASTRATEGICZNA_API UStaminaComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UStaminaComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Stamina|Value")
		float initialStaminaValue;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Stamina|Value")
		float staminaValue;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Stamina|Value")
		float regenerationValue;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Stamina|Value")
		float fatiqueValue;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void AdjustStamina(float value);
	bool CanRun();
	void StartResting();
	void Resting(float DeltaTime);
	void Fatique(float DeltaTime);

private:
	bool canRun = true;
	bool isResting = false;

};
