// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "BasicUnit.generated.h"

UCLASS()
class GRASTRATEGICZNA_API ABasicUnit : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ABasicUnit();

protected:

	FVector CurrentMoveLocation();



	// Called when the game starts or when spawned
	virtual void BeginPlay() override;



	void MoveToPoint(FVector Location);
public:	


	// Called every frame
	virtual void Tick(float DeltaTime) override;


};
