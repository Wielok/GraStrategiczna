// Fill out your copyright notice in the Description page of Project Settings.


#include "RangeFightComponent.h"
#include "BasicUnitV2.h"
#include "TestowyActor.h"
#include "MeleeFightComponent.h"
#include "Components/SphereComponent.h"

// Sets default values for this component's properties
URangeFightComponent::URangeFightComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	basicUnitController = Cast<ABasicUnitV2>(GetOwner());

	rangedSphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("RangedSphereComponent"));
	rangedSphereComponent->SetSphereRadius(1500.0f);
	rangedSphereComponent->SetCollisionResponseToChannel(ECollisionChannel::ECC_WorldDynamic,ECollisionResponse::ECR_Ignore);
	rangedSphereComponent->SetCollisionResponseToChannel(ECollisionChannel::ECC_GameTraceChannel1, ECollisionResponse::ECR_Ignore);
	rangedSphereComponent->bHiddenInGame = false;
	rangedSphereComponent->OnComponentBeginOverlap.AddDynamic(this, &URangeFightComponent::OnOverlapBeginRange);
	rangedSphereComponent->OnComponentEndOverlap.AddDynamic(this, &URangeFightComponent::OnOverlapEnd);
	if (GetOwner() != nullptr) 
	{
		rangedSphereComponent->SetupAttachment(GetOwner()->GetRootComponent());
	}
	// ...
}


// Called when the game starts
void URangeFightComponent::BeginPlay()
{
	Super::BeginPlay();
	// ...
	
}


// Called every frame
void URangeFightComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (basicUnitController->unitType == UnitType::RangeUnit && isInRange)
	{
		if (targetedUnitController == basicUnitController->meleeFightComponent->focusedEnemy) {
			FVector test1 = FMath::Lerp(basicUnitController->GetActorLocation(), targetedUnitController->GetActorLocation(), 0.4f);
			FVector test2 = FMath::Lerp(basicUnitController->GetActorLocation(), targetedUnitController->GetActorLocation(), 0.6f);
			test1.Z += 1000; 
			test2.Z += 1000;
			FVector MyControlPoints[4]{ basicUnitController->GetActorLocation(),test1,test2,targetedUnitController->GetActorLocation() };
			TArray<FVector> OutPoints;
			FVector::EvaluateBezier(MyControlPoints, 80, OutPoints);

			for (FVector point : OutPoints)
			{
				FActorSpawnParameters SpawnInfo;
				GetWorld()->SpawnActor<ATestowyActor>(point, basicUnitController->GetActorRotation(), SpawnInfo);

			}

		}
	}

	// ...
}

void URangeFightComponent::OnOverlapBeginRange(UPrimitiveComponent* newComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (basicUnitController->unitType == UnitType::RangeUnit)
	{
		isInRange = true;
		basicUnitController->StopMovingForRangedUnits();
		targetedUnitController = Cast<ABasicUnitV2>(OtherActor);
	
	}
}

void URangeFightComponent::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	isInRange = false;
	basicUnitController->StartMovingForRangedUnits();
}

