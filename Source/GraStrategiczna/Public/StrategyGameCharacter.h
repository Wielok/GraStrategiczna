// Fill out your copyright notice in the Description page of Project Settings.
#pragma once
#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "StrategyGameCharacter.generated.h"

class ABasicUnitV2;
class UCameraComponent;
class USpringArmComponent;

UCLASS()
class GRASTRATEGICZNA_API AStrategyGameCharacter : public ACharacter
{
	GENERATED_BODY()

public:

	AStrategyGameCharacter();

protected:

	bool bMove=false;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UCameraComponent* CameraComp;


	void MoveForward(float Value);

	void MoveRight(float Value);

	void TurnAtRate(float Rate);

	void LookUpAtRate(float Rate);

	void MoveCamera();

	void StopMoveCamera(); 

	void ChangeDistance(float Rate);

	void OnClickLeft();

	void OnClickRight();


	virtual void BeginPlay() override;

	TArray<ABasicUnitV2*> Units;
	TArray<ABasicUnitV2*> frendlyUnits;
	TArray<ABasicUnitV2*> enemyUnits;

	ABasicUnitV2* CurrentUnit = nullptr;
	ABasicUnitV2* enemyUnit = nullptr;
	
public:	

	UCharacterMovementComponent* MoveComp;

	float BaseDistanceChangeRate;
	float BaseTurnRate;
	float BaseLookUpRate;

	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void SeperateEnemiesWithFrendlyUnits();

private:

};
