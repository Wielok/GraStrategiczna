#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "BasicUnitV2.h"
#include "MeleeFightComponent.generated.h"

class ABasicUnitV2;

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class GRASTRATEGICZNA_API UMeleeFightComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UMeleeFightComponent();

protected:
	virtual void BeginPlay() override;

	ABasicUnitV2* basicUnitController;
	TArray<FVector> WeaponAttachPoint;

public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UPROPERTY(EditDefaultsOnly, Category = "RayCast Sockets")
	TArray<FName> WeaponAttachPointSocket;

	void DetectEnemies();
		
};
