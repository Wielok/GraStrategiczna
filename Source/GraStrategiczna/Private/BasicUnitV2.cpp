#include "BasicUnitV2.h"
#include "Components/BoxComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "GameFramework/PawnMovementComponent.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "NavigationSystem.h"
#include "MoveCompBasic.h"
#include "NavigationPath.h"
#include "Kismet/KismetMathLibrary.h"

ABasicUnitV2::ABasicUnitV2()
{
	PrimaryActorTick.bCanEverTick = true;

	RequiredDistanceToTarget = 1.0f;
	bEnd = true;
}

void ABasicUnitV2::BeginPlay()
{
	Super::BeginPlay();
}

void ABasicUnitV2::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void ABasicUnitV2::MoveToPoint(FVector Location)
{
	enumeration = 0;
	NavPath = UNavigationSystemV1::FindPathToLocationSynchronously(this, GetActorLocation(), Location);
	NextPoint = NextPathPoint();
	bEnd = false;
}

FVector ABasicUnitV2::NextPathPoint()
{
	if (NavPath && enumeration < NavPath->PathPoints.Num())
	{
		enumeration++;
		return NavPath->PathPoints[enumeration-1];
	}
	else 
	{
		bEnd = true;
	}
	return GetActorLocation();
}

void ABasicUnitV2::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (bEnd == false) 
	{
		float DistanceToTarget = FVector::Dist(GetActorLocation(), NextPoint);

		if (DistanceToTarget <= 100.0f) {
			NextPoint = NextPathPoint();
		}
		else
		{
			FVector moveVector = (NextPoint - GetActorLocation());
			FRotator currentRotation = GetActorRotation();
			FRotator findLookAtRotation = UKismetMathLibrary::FindLookAtRotation(GetActorLocation(), NextPoint);
			FRotator NewRot = FMath::RInterpTo(GetActorRotation(), findLookAtRotation, DeltaTime, 2);
			AddActorWorldTransform(FTransform(NewRot,moveVector.GetClampedToMaxSize(3),FVector::OneVector));
			SetActorLocation(GetActorLocation() + moveVector.GetClampedToMaxSize(3));
			SetActorRotation(FRotator(0.0f, NewRot.Yaw, 0.0f));
		}
	}
}