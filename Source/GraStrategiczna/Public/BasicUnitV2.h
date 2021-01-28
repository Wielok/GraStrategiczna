#pragma once

#include "CoreMinimal.h"
#include "NavigationPath.h"
#include "GameFramework/Character.h"
#include "MovingType.h"
#include "UnitType.h"
#include "UnitStatusType.h"
#include "BasicUnitV2.generated.h"


class UMeleeFightComponent;
class UHealthComponent;
class UStaminaComponent;
class USphereComponent;
class URangeFightComponent;

UCLASS()
class GRASTRATEGICZNA_API ABasicUnitV2 : public ACharacter
{
	GENERATED_BODY()

public:
	ABasicUnitV2();

	void MoveToPoint(FVector Location);
	void MoveToEnemy(AActor* Actor);
	void AttackEnemy(ABasicUnitV2* enemyUnit);

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Test)
		UHealthComponent* healthComponent;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Test)
		UStaminaComponent* staminaComponent;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Test)
		URangeFightComponent* rangeFightComponent;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SphereComponent")
		USphereComponent* sphereComponent;

	UFUNCTION()
		virtual void OnOverlapBegin(class UPrimitiveComponent* newComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	void NextPathPointToEnemy();
	FVector NextPathPoint();
	virtual void BeginPlay() override;


	FVector NextPoint;
	FVector EnemyPosition;
	UNavigationPath* NavPath;

	int enumeration;
	float MovementForce;
	float RequiredDistanceToTarget = 1.0f;
	bool bUseVelocityChange;
	bool bEnd = true;
	bool isAtacking = false;

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Test)
		UMeleeFightComponent* meleeFightComponent;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MoveState")
		UnitType unitType = UnitType::MeleeUnit;
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

	void GetDmg(float dmg);

	void StopMovingForRangedUnits();
	void StartMovingForRangedUnits();

	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	


};
