// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "UnitSpawnerActor.h"
#include "StrategyGameCharacter.h"
#include "GameController.generated.h"

class AUnitSpawnerActor;
class AStrategyGameCharacter;

UCLASS()
class GRASTRATEGICZNA_API AGameController : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGameController();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UnitSpawners")
		TArray <AUnitSpawnerActor*> unitSpawners;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	TArray<AStrategyGameCharacter*> Players;

};
