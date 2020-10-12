#include "BasicUnitV2.h"
#include "Components/BoxComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "GameFramework/PawnMovementComponent.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "NavigationSystem.h"
#include "MoveCompBasic.h"
#include "NavigationPath.h"
#include "Kismet/KismetMathLibrary.h"
#include "MeleeFightComponent.h"

ABasicUnitV2::ABasicUnitV2()
{
	PrimaryActorTick.bCanEverTick = true;

	meleeFightComponent=CreateDefaultSubobject<UMeleeFightComponent>(TEXT("MeleeFightComponent"));
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
		return NavPath->PathPoints[enumeration - 1];
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
	meleeFightComponent->DetectEnemies();

	if (bEnd == false)
	{
		float DistanceToTarget = FVector::Dist(GetActorLocation(), NextPoint);

		if (DistanceToTarget <= 100.0f) {
			NextPoint = NextPathPoint();
		}
		else
		{
			FVector currentlocation = GetActorLocation();
			FRotator currentRotation = GetActorRotation();
			FRotator findLookAtRotation = UKismetMathLibrary::FindLookAtRotation(GetActorLocation(), NextPoint);
			FRotator NewRot;
			switch (moveType) {
			case 1:
				NewRot = FMath::RInterpConstantTo(currentRotation, findLookAtRotation, DeltaTime, WalkRotationSpeed);
				if ((int)NewRot.Yaw == (int)currentRotation.Yaw)
				{
					FVector moveVector = FMath::VInterpConstantTo(GetActorLocation(), NextPoint, DeltaTime, WalkSpeed);
					//SetActorLocation(moveVector);
					AddMovementInput(moveVector-currentlocation);
				}
				SetActorRotation(FRotator(0.0f, NewRot.Yaw, 0.0f));
				break;
			case 2:
				NewRot = FMath::RInterpConstantTo(currentRotation, findLookAtRotation, DeltaTime, RunningRotationSpeed);
				FVector moveVector = FMath::VInterpConstantTo(GetActorLocation(), NextPoint, DeltaTime, RunningSpeed);
				//SetActorLocation(moveVector);
				AddMovementInput(moveVector-currentlocation);
				SetActorRotation(FRotator(0.0f, NewRot.Yaw, 0.0f));
				break;

			}

		}
	}
}