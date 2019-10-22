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
	MeshComp->SetCanEverAffectNavigation(false);
	MeshComp->SetSimulatePhysics(true);
	RootComponent = MeshComp;
	


	//MoveComp = CreateDefaultSubobject<UMoveCompBasic>(TEXT("MoveComp"));
	//MoveComp->UpdatedComponent = RootComponent;
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RequiredDistanceToTarget = 100.0f;
	bEnd = true;

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
	EndPoint = Location;
	NextPoint = NextPathPoint();
	bEnd = false;
}

FVector ABasicUnit::NextPathPoint()
{

	UNavigationPath* NavPath =UNavigationSystemV1::FindPathToLocationSynchronously(this, GetActorLocation(), EndPoint);

	if (NavPath->PathPoints.Num() > 1) {
		return NavPath->PathPoints[1];
	}
	else {
		bEnd = true;
	}
	return GetActorLocation();
}



// Called every frame
void ABasicUnit::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (bEnd == false) {
		float DistanceToTarget = (GetActorLocation() - NextPoint).Size();

		if (DistanceToTarget <= RequiredDistanceToTarget) {
			NextPoint = NextPathPoint();


		}
		else {
			FVector ForceDirection = NextPoint - GetActorLocation();

			ForceDirection.Normalize();

			ForceDirection *= (-0.2);
			MeshComp->AddForce(ForceDirection,NAME_None,bUseVelocityChange);
		}
	}
}

UPawnMovementComponent* ABasicUnit::GetMovementComponent() const
{
	return MoveComp;
}