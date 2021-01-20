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
#include "HealthComponent.h"
#include "StaminaComponent.h"
#include "MovingType.h"

ABasicUnitV2::ABasicUnitV2()
{
	PrimaryActorTick.bCanEverTick = true;

	meleeFightComponent = CreateDefaultSubobject<UMeleeFightComponent>(TEXT("MeleeFightComponent"));
	healthComponent = CreateDefaultSubobject<UHealthComponent>(TEXT("HealthComponent"));
	staminaComponent = CreateDefaultSubobject<UStaminaComponent>(TEXT("StaminaComponent"));
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
	meleeFightComponent->SetFocuesedEnemy(nullptr);
	enumeration = 0;
	NavPath = UNavigationSystemV1::FindPathToLocationSynchronously(this, GetActorLocation(), Location);
	NextPoint = NextPathPoint();
	bEnd = false;
}

void ABasicUnitV2::AttackEnemy(ABasicUnitV2* enemyUnit)
{
	meleeFightComponent->SetFocuesedEnemy(enemyUnit);
}

FVector ABasicUnitV2::NextPathPoint()
{
	if (NavPath && enumeration < NavPath->PathPoints.Num())
	{
		return NavPath->PathPoints[enumeration++];
	}
	else
	{
		bEnd = true;
	}
	return GetActorLocation();
}

FVector ABasicUnitV2::NextPathPointToEnemy()
{
	return GetActorLocation();
}

void ABasicUnitV2::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	meleeFightComponent->DetectEnemies();


	if (healthComponent->IsAlive()) {
		if (bEnd == false)
		{
			float DistanceToTarget = FVector::Dist(GetActorLocation(), NextPoint);

			if (DistanceToTarget <= 100.0f) {
				if (meleeFightComponent->IsEnemySet()) {
					NextPoint = NextPathPoint();
				} 
				else
				{
					NextPoint = NextPathPointToEnemy();
				}
			}
			else
			{
				FVector currentlocation = GetActorLocation();
				FRotator currentRotation = GetActorRotation();
				FRotator findLookAtRotation = UKismetMathLibrary::FindLookAtRotation(GetActorLocation(), NextPoint);
				FRotator NewRot;
				if (!(staminaComponent->CanRun())) {
					moveType = MovingType::Walk;
					staminaComponent->StartResting();
				}
				else {
					moveType = MovingType::Running;
				}

				switch (moveType) {
				case MovingType::Walk:
					NewRot = FMath::RInterpConstantTo(currentRotation, findLookAtRotation, DeltaTime, WalkRotationSpeed);
					if ((int)NewRot.Yaw == (int)currentRotation.Yaw)
					{
						FVector moveVector = FMath::VInterpConstantTo(GetActorLocation(), NextPoint, DeltaTime, WalkSpeed);
						AddMovementInput(moveVector - currentlocation);
					}
					SetActorRotation(FRotator(0.0f, NewRot.Yaw, 0.0f));
					break;
				case MovingType::Running:
					NewRot = FMath::RInterpConstantTo(currentRotation, findLookAtRotation, DeltaTime, RunningRotationSpeed);
					FVector moveVector = FMath::VInterpConstantTo(GetActorLocation(), NextPoint, DeltaTime, RunningSpeed);
					AddMovementInput(moveVector - currentlocation);
					SetActorRotation(FRotator(0.0f, NewRot.Yaw, 0.0f));
					staminaComponent->Fatique(DeltaTime);
					break;
				}
			}
		}
	}
}