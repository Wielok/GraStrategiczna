// Fill out your copyright notice in the Description page of Project Settings.


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
#include "BasicUnit.h"

// Sets default values
AStrategyGameCharacter::AStrategyGameCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	/*
	static ConstructorHelpers::FObjectFinder<TSubclassOf<ATestowyActor>>Box(TEXT("Class'/Script/GraStrategiczna.TestowyActor'"));

	if (Box.Succeeded())
	{
		ProjectileClass2=Box.Object;
		
	}*/



	// set our turn rates for input
	BaseTurnRate = 90.f;
	BaseLookUpRate = 90.f;
	BaseDistanceChangeRate = 45.f;



	//GetMesh()->SetCollisionResponseToChannel(COLLISION_WEAPON, ECR_Ignore);
	//GetCapsuleComponent()->SetCollisionResponseToChannel(COLLISION_WEAPON, ECR_Ignore);

	CameraComp = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComp"));
	CameraComp->bUsePawnControlRotation = true;
	CameraComp->SetupAttachment(RootComponent);





	


}

// Called when the game starts or when spawned
void AStrategyGameCharacter::BeginPlay()
{
	Super::BeginPlay();

	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ABasicUnit::StaticClass(), Units);

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


	PlayerInputComponent->BindAction("onClick", IE_Pressed, this, &AStrategyGameCharacter::onClick);
	PlayerInputComponent->BindAction("onClickRight", IE_Pressed, this, &AStrategyGameCharacter::onClickRight);

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
	/*
	if((SpringArmComp->TargetArmLength + (Rate * BaseDistanceChangeRate))>2.0 && (SpringArmComp->TargetArmLength + (Rate * BaseDistanceChangeRate))<10000.0f)
	SpringArmComp->TargetArmLength += (Rate* BaseDistanceChangeRate);*/
	
		FQuat Rotation = CameraComp->GetComponentTransform().GetRotation();
		//FRotator Rotation = CameraComp->GetWorldRotation();
		FVector vForward = Rotation.RotateVector(FVector(100000.0f,0.0f,0.0f));

		//FString TraceString;

		//TraceString += FString::Printf(TEXT("%s."), *CameraComp->GetComponentRotation().ToString);
		//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TraceString);


		AddMovementInput(vForward, Rate*1000000000.0f);
		//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, "%s",*vForward.ToString());
	

}

void AStrategyGameCharacter::onClick()
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

		//Interaction->Location;
		
		FString TraceString;
		if (Interaction.GetActor() != nullptr)
		{
			
			
			CurrentUnit = nullptr;
			TraceString += FString::Printf(TEXT("%s."), *Interaction.Location.ToString());
			FActorSpawnParameters ActorSpawnParams;
			ActorSpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButDontSpawnIfColliding;
			GetWorld()->SpawnActor<ATestowyActor>(ProjectileClass, Interaction.Location,FRotator(0.0f,0.0f,0.0f), ActorSpawnParams);
			for (int i = 0; i < Units.Num(); i++) {
				if (Units[i] == Interaction.GetActor()) {
					CurrentUnit = Cast<ABasicUnit>(Interaction.GetActor());
					GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red,"jednostka");
				
				}
				
			}



		}
		/*
		if (Interaction.GetComponent() != nullptr)
		{
			TraceString += FString::Printf(TEXT("%s."), *Interaction.Location.ToString());

			FActorSpawnParameters ActorSpawnParams;
			ActorSpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButDontSpawnIfColliding;

			// spawn the projectile at the muzzle
			GetWorld()->SpawnActor<ATestowyActor>(ProjectileClass, Interaction.Location, FRotator(0.0f, 0.0f, 0.0f), ActorSpawnParams);

		}*/
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TraceString);
	}
	
	
}

void AStrategyGameCharacter::onClickRight()
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

			//Interaction->Location;

			FString TraceString;
			if (Interaction.GetActor() != nullptr)
			{
				FActorSpawnParameters ActorSpawnParams;
				ActorSpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButDontSpawnIfColliding;
				GetWorld()->SpawnActor<ATestowyActor>(ProjectileClass, Interaction.Location, FRotator(0.0f, 0.0f, 0.0f), ActorSpawnParams);
				CurrentUnit->MoveToPoint(Interaction.Location);
				GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, "Kurczak");




			}

		}
	}
	

}