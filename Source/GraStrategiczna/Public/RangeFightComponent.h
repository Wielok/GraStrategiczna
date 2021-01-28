// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "RangeFightComponent.generated.h"

class USphereComponent;
class ABasicUnitV2;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class GRASTRATEGICZNA_API URangeFightComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	URangeFightComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SphereComponent")
		USphereComponent* rangedSphereComponent;

	UFUNCTION()
		virtual void OnOverlapBeginRange(class UPrimitiveComponent* newComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
		void OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	ABasicUnitV2* basicUnitController;
	ABasicUnitV2* targetedUnitController;

	
	bool isRanged = false;
	bool isInRange = false;
};
