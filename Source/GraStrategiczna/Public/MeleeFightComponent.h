#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "BasicUnitV2.h"
#include "MeleeFightComponent.generated.h"

class ABasicUnitV2;
class USphereComponent;

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class GRASTRATEGICZNA_API UMeleeFightComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UMeleeFightComponent();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SphereComponent")
		USphereComponent* sphereComponent;

	ABasicUnitV2* basicUnitController;
	TArray<FVector> WeaponAttachPoint;


	virtual void BeginPlay() override;

public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UPROPERTY(EditDefaultsOnly, Category = "RayCast Sockets")
	TArray<FName> WeaponAttachPointSocket;

	ABasicUnitV2* focusedEnemy;

	void DetectEnemies();

	void SetFocuesedEnemy(ABasicUnitV2* enemy);

	bool IsEnemySet();
		
};
