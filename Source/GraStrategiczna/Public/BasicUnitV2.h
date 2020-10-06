#pragma once

#include "CoreMinimal.h"
#include "NavigationPath.h"
#include "GameFramework/Character.h"
#include "BasicUnitV2.generated.h"

UCLASS()
class GRASTRATEGICZNA_API ABasicUnitV2 : public ACharacter
{
	GENERATED_BODY()

public:
	ABasicUnitV2();

	void MoveToPoint(FVector Location);

protected:
	FVector NextPathPoint();
	virtual void BeginPlay() override;

	FVector NextPoint;
	UNavigationPath* NavPath;

	int enumeration;
	float MovementForce;
	float RequiredDistanceToTarget;
	bool bUseVelocityChange;
	bool bEnd;

public:
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
};
