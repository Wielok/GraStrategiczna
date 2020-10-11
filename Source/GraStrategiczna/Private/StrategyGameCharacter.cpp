#include "StrategyGameCharacter.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/InputSettings.h"
#include "GameFramework/PawnMovementComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "..\Public\StrategyGameCharacter.h"
#include "TestowyActor.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "BasicUnitV2.h"

// Sets default values
AStrategyGameCharacter::AStrategyGameCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	BaseTurnRate = 90.f;
	BaseLookUpRate = 90.f;
	BaseDistanceChangeRate = 45.f;

	CameraComp = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComp"));
	CameraComp->bUsePawnControlRotation = true;
	CameraComp->SetupAttachment(RootComponent);

}

// Called when the game starts or when spawned
void AStrategyGameCharacter::BeginPlay()
{
	Super::BeginPlay();

	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ABasicUnitV2::StaticClass(), Units);

	MoveComp = GetCharacterMovement();
	MoveComp->SetMovementMode(MOVE_Flying);
	MoveComp->bCheatFlying = true;
	MoveComp->MaxAcceleration = 100000.0f;
	MoveComp->BrakingDecelerationFlying = 100000.0f;
}

// Called every frame
void AStrategyGameCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void AStrategyGameCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveForward", this, &AStrategyGameCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AStrategyGameCharacter::MoveRight);


	PlayerInputComponent->BindAxis("TurnRate", this, &AStrategyGameCharacter::TurnAtRate);
	PlayerInputComponent->BindAxis("LookUpRate", this, &AStrategyGameCharacter::LookUpAtRate);

	PlayerInputComponent->BindAxis("ArmLength", this, &AStrategyGameCharacter::ChangeDistance);


	PlayerInputComponent->BindAction("OnClickLeft", IE_Pressed, this, &AStrategyGameCharacter::OnClickLeft);
	PlayerInputComponent->BindAction("OnClickRight", IE_Pressed, this, &AStrategyGameCharacter::OnClickRight);

	PlayerInputComponent->BindAction("MoveCamera", IE_Pressed, this, &AStrategyGameCharacter::MoveCamera);
	PlayerInputComponent->BindAction("MoveCamera", IE_Released, this, &AStrategyGameCharacter::StopMoveCamera);
}

void AStrategyGameCharacter::MoveRight(float Value)
{
	if (Value != 0.0f)
	{
		AddMovementInput(GetActorRightVector(), Value);
	}
}

void AStrategyGameCharacter::MoveForward(float Value)
{
	if (Value != 0.0f)
	{
		if (bMove == true)
		{
			FQuat Rotation = CameraComp->GetComponentTransform().GetRotation();
			FVector vForward = Rotation.RotateVector(FVector(1.0f, 0.0f, 0.0f));
			AddMovementInput(vForward, Value * 1.0f);
		}
		else
		{
			AddMovementInput(GetActorForwardVector(), Value);
		}
	}
}

void AStrategyGameCharacter::LookUpAtRate(float Rate)
{

	if (bMove) {

		AddControllerPitchInput(Rate * BaseLookUpRate * GetWorld()->GetDeltaSeconds());
	}
}

void AStrategyGameCharacter::TurnAtRate(float Rate)
{
	if (bMove) {

		AddControllerYawInput(Rate * BaseTurnRate * GetWorld()->GetDeltaSeconds());
	}
}

void AStrategyGameCharacter::MoveCamera()
{
	bMove = true;
}

void AStrategyGameCharacter::StopMoveCamera()
{
	bMove = false;
}

void AStrategyGameCharacter::ChangeDistance(float Rate)
{
	FVector vForward = FVector(0.0f, 0.0f, 1.0f);
	AddMovementInput(vForward, Rate);
}

void AStrategyGameCharacter::OnClickLeft()
{
	APlayerController* PlayerController = Cast<APlayerController>(GetController());
	if (PlayerController != nullptr)
	{
		FVector mouseLocation, mouseDirection;
		PlayerController->DeprojectMousePositionToWorld(mouseLocation, mouseDirection);
		FVector TraceEnd = (mouseLocation + (mouseDirection * 100000));

		FCollisionQueryParams QueryParmas;
		QueryParmas.AddIgnoredActor(this);
		QueryParmas.bTraceComplex = true;

		FHitResult Interaction;

		GetWorld()->LineTraceSingleByChannel(Interaction, mouseLocation, TraceEnd, ECC_GameTraceChannel1, QueryParmas);

		FString TraceString;
		if (Interaction.GetActor() != nullptr)
		{
			CurrentUnit = nullptr;
			FActorSpawnParameters ActorSpawnParams;
			ActorSpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButDontSpawnIfColliding;
			for (int i = 0; i < Units.Num(); i++)
			{
				if (Units[i] == Interaction.GetActor())
				{
					CurrentUnit = Cast<ABasicUnitV2>(Interaction.GetActor());
				}

			}
		}
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TraceString);
	}
}

void AStrategyGameCharacter::OnClickRight()
{
	if (CurrentUnit != nullptr) {

		APlayerController* PlayerController = Cast<APlayerController>(GetController());
		if (PlayerController != nullptr)
		{
			FVector mouseLocation, mouseDirection;
			PlayerController->DeprojectMousePositionToWorld(mouseLocation, mouseDirection);
			FVector TraceEnd = (mouseLocation + (mouseDirection * 100000));
			FCollisionQueryParams QueryParmas;
			QueryParmas.AddIgnoredActor(this);
			QueryParmas.bTraceComplex = true;
			FHitResult Interaction;
			GetWorld()->LineTraceSingleByChannel(Interaction, mouseLocation, TraceEnd, ECC_GameTraceChannel1, QueryParmas);
			FString TraceString;
			if (Interaction.GetActor() != nullptr)
			{
				FActorSpawnParameters ActorSpawnParams;
				ActorSpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButDontSpawnIfColliding;
				CurrentUnit->MoveToPoint(Interaction.Location);
			}

		}
	}
}