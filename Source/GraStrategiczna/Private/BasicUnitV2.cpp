// Fill out your copyright notice in the Description page of Project Settings.


#include "BasicUnitV2.h"
#include "Components/BoxComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "GameFramework/PawnMovementComponent.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "NavigationSystem.h"
#include "MoveCompBasic.h"
#include "NavigationPath.h"
// Sets default values
ABasicUnitV2::ABasicUnitV2()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;


	/*
	MeshComp = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("MeshComp"));
	MeshComp->SetCanEverAffectNavigation(false);
	MeshComp->SetSimulatePhysics(true);
	MeshComp->SetupAttachment(RootComponent);
	*/



	//MoveComp = CreateDefaultSubobject<UMoveCompBasic>(TEXT("MoveComp"));
	//MoveComp->UpdatedComponent = RootComponent;
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RequiredDistanceToTarget = 1.0f;
	bEnd = true;


}

// Called when the game starts or when spawned
void ABasicUnitV2::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame

// Called to bind functionality to input
void ABasicUnitV2::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ABasicUnitV2::MoveToPoint(FVector Location)
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, "odpowiada");
	EndPoint = Location;
	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, FString::SanitizeFloat(Location));

	NextPoint = NextPathPoint();
	bEnd = false;
}

FVector ABasicUnitV2::NextPathPoint()
{
	UNavigationPath* NavPath = UNavigationSystemV1::FindPathToLocationSynchronously(this, GetActorLocation(), EndPoint);



	if (NavPath && NavPath->PathPoints.Num() > 1)
	{
		// Return next point in the path

		return NavPath->PathPoints[1];
	}
	else {
		bEnd = true;
	}
	return GetActorLocation();
}



// Called every frame
void ABasicUnitV2::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);


	if (bEnd == false) {
		float DistanceToTarget = FVector::Dist(GetActorLocation(), NextPoint);

		if (DistanceToTarget <= 10.0f) {
			NextPoint = NextPathPoint();

		}
		else {
			FVector ForceDirection = NextPoint - GetActorLocation();
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, "rusza sie");
			ForceDirection.Normalize();

			ForceDirection *= 1000;
			//MeshComp->AddForce(ForceDirection,NAME_None,bUseVelocityChange);
			//UNavigationSystemV1::SimpleMoveToLocation(GetController(),NextPoint);
			UAIBlueprintHelperLibrary::SimpleMoveToLocation(GetController(), NextPoint);
		}
	}
}