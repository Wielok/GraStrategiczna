// Fill out your copyright notice in the Description page of Project Settings.


#include "StrategyGameCharacter.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/InputSettings.h"
#include "GameFramework/PawnMovementComponent.h"

// Sets default values
AStrategyGameCharacter::AStrategyGameCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;




	// set our turn rates for input
	BaseTurnRate = 45.f;
	BaseLookUpRate = 45.f;

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