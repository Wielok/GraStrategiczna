// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "BasicUnitV2.generated.h"

UCLASS()
class GRASTRATEGICZNA_API ABasicUnitV2 : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ABasicUnitV2();

	void MoveToPoint(FVector Location);

protected:

	FVector NextPathPoint();

	FVector NextPoint;



	//UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
		//USkeletalMeshComponent* MeshComp;
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


	float MovementForce;

	float RequiredDistanceToTarget;

	FVector EndPoint;

	bool bUseVelocityChange;
	bool bEnd;

public:


	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
