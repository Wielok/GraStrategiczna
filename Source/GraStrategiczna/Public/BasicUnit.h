// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "BasicUnit.generated.h"

class UBoxComponent;
class USkeletalMeshComponent;
class UMoveCompBasic;

UCLASS()
class GRASTRATEGICZNA_API ABasicUnit : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ABasicUnit();

	void MoveToPoint(FVector Location);

protected:

	FVector NextPathPoint(FVector Location);

	//void CurrentMoveLocation();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
		UMoveCompBasic* MoveComp;

	//UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	//UBoxComponent* BoxComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	USkeletalMeshComponent* MeshComp;
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	

	virtual UPawnMovementComponent* GetMovementComponent() const override;
	
public:	


	// Called every frame
	virtual void Tick(float DeltaTime) override;


};
