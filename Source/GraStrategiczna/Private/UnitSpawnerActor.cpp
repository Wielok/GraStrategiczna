// Fill out your copyright notice in the Description page of Project Settings.


#include "UnitSpawnerActor.h"

// Sets default values
AUnitSpawnerActor::AUnitSpawnerActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AUnitSpawnerActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AUnitSpawnerActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AUnitSpawnerActor::SpawnUnit(FVector location, FRotator rotation)
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Orange, FString::Printf(TEXT("Spawning")));

	ABasicUnitV2* spawnedUnit = (GetWorld()->SpawnActor<ABasicUnitV2>(unitRef, GetActorLocation(), GetActorRotation()));
	spawnedUnit->unitStatusType = unitStatusType;
}

