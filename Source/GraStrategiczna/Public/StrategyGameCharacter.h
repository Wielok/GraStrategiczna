// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "StrategyGameCharacter.generated.h"



class UCameraComponent;
class USpringArmComponent;


UCLASS()
class GRASTRATEGICZNA_API AStrategyGameCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AStrategyGameCharacter();

protected:

	bool bMove=false;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
		UCameraComponent* CameraComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
		USpringArmComponent* SpringArmComp;

	void MoveForward(float Value);

	void MoveRight(float Value);

	void TurnAtRate(float Rate);

	void LookUpAtRate(float Rate);

	void MoveCamera();

	void StopMoveCamera(); 

	void ChangeDistance(float Rate);

	void onClick();


	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	

	float BaseDistanceChangeRate;

	float BaseTurnRate;

	float BaseLookUpRate;


	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
