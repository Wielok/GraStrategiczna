#include "BasicUnitV2.h"
#include "Components/BoxComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "GameFramework/PawnMovementComponent.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "NavigationSystem.h"
#include "MoveCompBasic.h"
#include "NavigationPath.h"
#include "Components/SphereComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "MeleeFightComponent.h"
#include "HealthComponent.h"
#include "RangeFightComponent.h"
#include "StaminaComponent.h"
#include "UnitType.h"
#include "MovingType.h"

ABasicUnitV2::ABasicUnitV2()
{
	PrimaryActorTick.bCanEverTick = true;

	meleeFightComponent = CreateDefaultSubobject<UMeleeFightComponent>(TEXT("MeleeFightComponent"));
	healthComponent = CreateDefaultSubobject<UHealthComponent>(TEXT("HealthComponent"));
	staminaComponent = CreateDefaultSubobject<UStaminaComponent>(TEXT("StaminaComponent"));
	rangeFightComponent = CreateDefaultSubobject<URangeFightComponent>(TEXT("RangeFightComponent"));


	sphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComponent"));
	sphereComponent->SetSphereRadius(300.0f);
	sphereComponent->SetCollisionResponseToChannel(ECollisionChannel::ECC_WorldDynamic, ECollisionResponse::ECR_Ignore);
	sphereComponent->SetCollisionResponseToChannel(ECollisionChannel::ECC_EngineTraceChannel1, ECollisionResponse::ECR_Ignore);
	sphereComponent->bHiddenInGame = false;
	sphereComponent->OnComponentBeginOverlap.AddDynamic(this, &ABasicUnitV2::OnOverlapBegin);
	sphereComponent->SetupAttachment(GetRootComponent());

}

void ABasicUnitV2::BeginPlay()
{
	Super::BeginPlay();
	if (unitType == UnitType::RangeUnit)
	{

	}
}

void ABasicUnitV2::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void ABasicUnitV2::MoveToPoint(FVector Location)
{
	moveType = MovingType::Running;
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Orange, FString::Printf(TEXT("point")));
	meleeFightComponent->SetFocuesedEnemy(nullptr);
	enumeration = 0;
	NavPath = UNavigationSystemV1::FindPathToLocationSynchronously(this, GetActorLocation(), Location);
	NextPoint = NextPathPoint();
	bEnd = false;
}



void ABasicUnitV2::OnOverlapBegin(UPrimitiveComponent* newComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (!(unitType == UnitType::RangeUnit))
	{
		ABasicUnitV2* entry = Cast<ABasicUnitV2>(OtherActor);
		if (entry == meleeFightComponent->focusedEnemy) {
			meleeFightComponent->focusedEnemy->GetDmg(meleeFightComponent->DmgValue);
		}
	}
}


void ABasicUnitV2::MoveToEnemy(AActor* Actor)
{
	enumeration = 0;
	EnemyPosition = Actor->GetActorLocation();
	NavPath = UNavigationSystemV1::FindPathToActorSynchronously(this, GetActorLocation(), Actor);
	NextPoint = NextPathPoint();
	bEnd = false;
}

void ABasicUnitV2::AttackEnemy(ABasicUnitV2* enemyUnit)
{
	meleeFightComponent->SetFocuesedEnemy(enemyUnit);
	MoveToEnemy(enemyUnit);
}

FVector ABasicUnitV2::NextPathPoint()
{
	if (NavPath && enumeration < NavPath->PathPoints.Num())
	{
		return NavPath->PathPoints[enumeration++];
	}
	else
	{
		if (!meleeFightComponent->IsEnemySet()) {
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Orange, FString::Printf(TEXT("end")));
			bEnd = true;
		}
	}
	return GetActorLocation();
}

void ABasicUnitV2::NextPathPointToEnemy()
{
	if (meleeFightComponent->IsEnemySet()) {
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Orange, FString::Printf(TEXT("Attack2")));
		FVector currenEnemyPosition = meleeFightComponent->focusedEnemy->GetActorLocation();
		if (currenEnemyPosition != EnemyPosition) {
			MoveToEnemy(meleeFightComponent->focusedEnemy);
			NextPoint = NextPathPoint();
		}
	}
}

void ABasicUnitV2::GetDmg(float dmg)
{

	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Orange, FString::Printf(TEXT("DMG")));
	healthComponent->DealDmg(dmg, true);
}

void ABasicUnitV2::StopMovingForRangedUnits()
{
	isAtacking = true;
	moveType = MovingType::Fight;
}

void ABasicUnitV2::StartMovingForRangedUnits()
{
	isAtacking = false;
}

void ABasicUnitV2::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	meleeFightComponent->DetectEnemies();

	if (healthComponent->IsAlive()) {
		if (meleeFightComponent->IsEnemySet())
		{
			float value = (meleeFightComponent->focusedEnemy->GetActorLocation() - EnemyPosition).Size();
			if (value > 100.0f) {
				GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Orange, FString::Printf(TEXT("pos2")));
				MoveToEnemy(meleeFightComponent->focusedEnemy);
			}
		}
		if (bEnd == false)
		{

			float DistanceToTarget = FVector::Dist(GetActorLocation(), NextPoint);
			if (DistanceToTarget <= 100.0f)
			{
				NextPoint = NextPathPoint();
			}
			else
			{
				FVector currentlocation = GetActorLocation();
				FRotator currentRotation = GetActorRotation();
				FRotator findLookAtRotation = UKismetMathLibrary::FindLookAtRotation(GetActorLocation(), NextPoint);
				FRotator NewRot;
				if (moveType != MovingType::Fight) {
					if (isAtacking && meleeFightComponent->focusedEnemy) {
						moveType = MovingType::Fight;
					}
					else if (!(staminaComponent->CanRun())) {
						moveType = MovingType::Walk;
						staminaComponent->StartResting();
					}
					else {
						moveType = MovingType::Running;
					}
				}

				switch (moveType)
				{
				case MovingType::Walk: {
					NewRot = FMath::RInterpConstantTo(currentRotation, findLookAtRotation, DeltaTime, WalkRotationSpeed);
					if ((int)NewRot.Yaw == (int)currentRotation.Yaw)
					{
						FVector moveVector = FMath::VInterpConstantTo(GetActorLocation(), NextPoint, DeltaTime, WalkSpeed);
						AddMovementInput(moveVector - currentlocation);
					}
					SetActorRotation(FRotator(0.0f, NewRot.Yaw, 0.0f));
					break; }
				case MovingType::Running: {
					NewRot = FMath::RInterpConstantTo(currentRotation, findLookAtRotation, DeltaTime, RunningRotationSpeed);
					FVector moveVector = FMath::VInterpConstantTo(GetActorLocation(), NextPoint, DeltaTime, RunningSpeed);
					AddMovementInput(moveVector - currentlocation);
					SetActorRotation(FRotator(0.0f, NewRot.Yaw, 0.0f));
					staminaComponent->Fatique(DeltaTime);
					break; }
				case MovingType::Fight: {
					NewRot = FMath::RInterpConstantTo(currentRotation, findLookAtRotation, DeltaTime, RunningRotationSpeed);
					SetActorRotation(FRotator(0.0f, NewRot.Yaw, 0.0f));

					break; }
				}
			}
		}
	}

	else {
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Orange, FString::Printf(TEXT(" Dead %s"), *GetName()));
		Destroy();
	}
}