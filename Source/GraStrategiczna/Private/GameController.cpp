// Fill out your copyright notice in the Description page of Project Settings.


#include "GameController.h"
#include "StrategyGameCharacter.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AGameController::AGameController()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AGameController::BeginPlay()
{
	Super::BeginPlay();

	for (AUnitSpawnerActor* spawner : unitSpawners) {
		spawner->SpawnUnit(this->GetActorLocation(), this->GetActorRotation());
	}
	TArray<AActor*> FoundPlayers;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AStrategyGameCharacter::StaticClass(), FoundPlayers);
	for (AActor* character : FoundPlayers) {
		AStrategyGameCharacter* player = Cast<AStrategyGameCharacter>(character);
		player->SeperateEnemiesWithFrendlyUnits();

	}
}

// Called every frame
void AGameController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

