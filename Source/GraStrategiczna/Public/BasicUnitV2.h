#pragma once

#include "CoreMinimal.h"
#include "NavigationPath.h"
#include "GameFramework/Character.h"
#include "MeleeFightActor.h"
#include "MovingType.h"
#include "BasicUnitV2.generated.h"

class UMeleeFightComponent;

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

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Test)
	UMeleeFightComponent* meleeFightComponent;


	int enumeration;
	float MovementForce;
	float RequiredDistanceToTarget = 1.0f;
	bool bUseVelocityChange;
	bool bEnd = true;

public:
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MoveState")
	TEnumAsByte<MovingType> moveType;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "MoveState|Walk")
	int WalkSpeed = 3;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "MoveState|Walk")
	int WalkRotationSpeed = 2;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "MoveState|Running")
	int RunningSpeed = 5;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "MoveState|Running")
	int RunningRotationSpeed = 3;
};
