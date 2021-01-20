#pragma once

#include "CoreMinimal.h"
#include "NavigationPath.h"
#include "GameFramework/Character.h"
#include "MovingType.h"
#include "UnitStatusType.h"
#include "BasicUnitV2.generated.h"

class UMeleeFightComponent;
class UHealthComponent;
class UStaminaComponent;

UCLASS()
class GRASTRATEGICZNA_API ABasicUnitV2 : public ACharacter
{
	GENERATED_BODY()

public:
	ABasicUnitV2();

	void MoveToPoint(FVector Location);
	void AttackEnemy(ABasicUnitV2* enemyUnit);

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Test)
		UHealthComponent* healthComponent;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Test)
		UStaminaComponent* staminaComponent;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Test)
		UMeleeFightComponent* meleeFightComponent;

	FVector NextPathPointToEnemy();
	FVector NextPathPoint();
	virtual void BeginPlay() override;

	FVector NextPoint;
	UNavigationPath* NavPath;

	int enumeration;
	float MovementForce;
	float RequiredDistanceToTarget = 1.0f;
	bool bUseVelocityChange;
	bool bEnd = true;

public:
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MoveState")
		MovingType moveType = MovingType::Idle;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UnitStatus")
		UnitStatusType unitStatusType = UnitStatusType::Owner;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "MoveState|Walk")
		int WalkSpeed = 3;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "MoveState|Walk")
		int WalkRotationSpeed = 2;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "MoveState|Running")
		int RunningSpeed = 5;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "MoveState|Running")
		int RunningRotationSpeed = 3;
};
