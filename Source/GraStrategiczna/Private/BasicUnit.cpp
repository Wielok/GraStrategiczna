// Fill out your copyright notice in the Description page of Project Settings.


#include "BasicUnit.h"
#include "..\Public\BasicUnit.h"
//#include "Components/BoxComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "GameFramework/PawnMovementComponent.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "NavigationSystem.h"
#include "MoveCompBasic.h"
#include "NavigationPath.h"

// Sets default values
ABasicUnit::ABasicUnit()
{
	PrimaryActorTick.bCanEverTick = true;
	/*
	BoxComp = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxCollision"));
	BoxComp->SetCanEverAffectNavigation(false);
	BoxComp->bDynamicObstacle = true;
	*/
	//RootComponent = BoxComp;

	MeshComp = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("MeshComp"));
	RootComponent = MeshComp;
	MeshComp->SetCanEverAffectNavigation(false);

	MoveComp = CreateDefaultSubobject<UMoveCompBasic>(TEXT("MoveComp"));
	MoveComp->UpdatedComponent = RootComponent;
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

FVector ABasicUnit::NextPathPoint(FVector Location)
{

	UNavigationPath* NavPath =UNavigationSystemV1::FindPathToLocationSynchronously(this, GetActorLocation(), Location);

	if (NavPath->PathPoints.Num() > 1) {
		return NavPath->PathPoints[1];
	}
	return GetActorLocation();
}



// Called every frame
void ABasicUnit::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

UPawnMovementComponent* ABasicUnit::GetMovementComponent() const
{
	return MoveComp;
}