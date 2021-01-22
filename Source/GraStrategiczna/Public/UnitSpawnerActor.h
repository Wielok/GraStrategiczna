// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UnitType.h"
#include "BasicUnitV2.h"
#include "GameFramework/Actor.h"
#include "UnitSpawnerActor.generated.h"


UCLASS()
class GRASTRATEGICZNA_API AUnitSpawnerActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AUnitSpawnerActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UnitType")
		UnitType unitType = UnitType::BasicUnit;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UnitType|Ref")
		TSubclassOf<ABasicUnitV2> unitRef;


public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void SpawnUnit(FVector location, FRotator rotation);

};
