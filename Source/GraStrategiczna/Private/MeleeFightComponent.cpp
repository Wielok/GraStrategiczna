#include "MeleeFightComponent.h"
#include "Components/SphereComponent.h"
#include "DrawDebugHelpers.h"
#include "BasicUnitV2.h"

UMeleeFightComponent::UMeleeFightComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	basicUnitController = Cast<ABasicUnitV2>(GetOwner());

	// ...
}

// Called when the game starts
void UMeleeFightComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...

}

// Called every frame
void UMeleeFightComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UMeleeFightComponent::DetectEnemies()
{
	for (FName AttachPointSocket : WeaponAttachPointSocket)
	{
		WeaponAttachPoint.Add(basicUnitController->GetMesh()->GetSocketLocation(AttachPointSocket));
	}

	for (FVector AttachPoint : WeaponAttachPoint)
	{
		FVector TraceEnd = 10000 * basicUnitController->GetActorForwardVector();
		//DrawDebugLine(GetWorld(), AttachPoint, TraceEnd, FColor::Green, true, 1, 0, 1);
	}
}