// Fill out your copyright notice in the Description page of Project Settings.


#include "BasicUnit.h"
#include "AI/NavigationSystemBase.h"
#include "..\Public\BasicUnit.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"

// Sets default values
ABasicUnit::ABasicUnit()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ABasicUnit::BeginPlay()
{
	Super::BeginPlay();
	// spawns default controller (if not, there is no controller for NPC to control)
	
}

void ABasicUnit::MoveToPoint(FVector Location)
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, "odpowiada");
	UAIBlueprintHelperLibrary::SimpleMoveToLocation(GetController(), Location);
}



// Called every frame
void ABasicUnit::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}
/*// Assign next patrol point.
	if (CurrentPatrolPoint == nullptr || CurrentPatrolPoint == SecondPatrolPoint)
	{
		CurrentPatrolPoint = FirstPatrolPoint;
	}
	else
	{
		CurrentPatrolPoint = SecondPatrolPoint;
	}

	UNavigationSystem::SimpleMoveToActor(GetController(), CurrentPatrolPoint);*/