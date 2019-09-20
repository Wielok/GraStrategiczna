// Fill out your copyright notice in the Description page of Project Settings.


#include "StrategyGameCharacter.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/InputSettings.h"
#include "GameFramework/PawnMovementComponent.h"
#include "..\Public\StrategyGameCharacter.h"

// Sets default values
AStrategyGameCharacter::AStrategyGameCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;




	// set our turn rates for input
	BaseTurnRate = 90.f;
	BaseLookUpRate = 90.f;
	BaseDistanceChangeRate = 45.f;


	SpringArmComp = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArmComp"));
	SpringArmComp->bUsePawnControlRotation = true;
	SpringArmComp->SetupAttachment(RootComponent);
	//GetMesh()->SetCollisionResponseToChannel(COLLISION_WEAPON, ECR_Ignore);
	//GetCapsuleComponent()->SetCollisionResponseToChannel(COLLISION_WEAPON, ECR_Ignore);

	CameraComp = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComp"));
	CameraComp->SetupAttachment(SpringArmComp);



}

// Called when the game starts or when spawned
void AStrategyGameCharacter::BeginPlay()
{
	Super::BeginPlay();
	
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


	PlayerInputComponent->BindAction("onClick", IE_Pressed, this, &AStrategyGameCharacter::onClick);

	PlayerInputComponent->BindAction("MoveCamera",IE_Pressed,this, &AStrategyGameCharacter::MoveCamera);
	PlayerInputComponent->BindAction("MoveCamera", IE_Released, this, &AStrategyGameCharacter::StopMoveCamera);


}

void AStrategyGameCharacter::MoveRight(float Value)
{

	if (Value != 0.0f)
	{


		// add movement in that direction
		AddMovementInput(GetActorRightVector(), Value);
	}
}

void AStrategyGameCharacter::MoveForward(float Value)
{


	if (Value != 0.0f)
	{
		//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("This is an on screen message!"));

		// add movement in that direction
		AddMovementInput(GetActorForwardVector(), Value);
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

void AStrategyGameCharacter::MoveCamera() {
	bMove = true;
}

void AStrategyGameCharacter::StopMoveCamera() {
	bMove = false;
}

void AStrategyGameCharacter::ChangeDistance(float Rate) {

	if((SpringArmComp->TargetArmLength + (Rate * BaseDistanceChangeRate))>2.0 && (SpringArmComp->TargetArmLength + (Rate * BaseDistanceChangeRate))<1000.0f)
	SpringArmComp->TargetArmLength += (Rate* BaseDistanceChangeRate);

}

void AStrategyGameCharacter::onClick()
{
	APlayerController* PlayerController = Cast<APlayerController>(GetController());
	if (PlayerController != nullptr)
	{
		FVector mouseLocation, mouseDirection;

		//PlayerController->GetHitResultUnderCursor(ECollisionChannel::ECC_WorldDynamic, false, TraceResult);
		PlayerController->DeprojectMousePositionToWorld(mouseLocation, mouseDirection);


		FVector TraceEnd = (mouseLocation + (mouseDirection * 1000));

		FCollisionQueryParams QueryParmas;
		QueryParmas.AddIgnoredActor(this);
		QueryParmas.bTraceComplex = true;

		FHitResult Interaction;

		GetWorld()->LineTraceSingleByChannel(Interaction, mouseLocation, TraceEnd, ECC_GameTraceChannel1, QueryParmas);

		//Interaction->Location;

		FString TraceString;
		if (Interaction.GetActor() != nullptr)
		{
			TraceString += FString::Printf(TEXT("Trace Actor %s."), *Interaction.Location.ToString());
		}
		if (Interaction.GetComponent() != nullptr)
		{
			TraceString += FString::Printf(TEXT("Trace Comp %s."), *Interaction.Location.ToString());
		}
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TraceString);
	}
	
	
}
