// Fill out your copyright notice in the Description page of Project Settings.


#include "TestowyActor.h"

// Sets default values
ATestowyActor::ATestowyActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;


	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("VisualRepresentation"));
	static ConstructorHelpers::FObjectFinder<UStaticMesh> BoxVisualAsset(TEXT("StaticMesh'/Engine/VREditor/TransformGizmo/StartRotationHandleIndicator.StartRotationHandleIndicator'"));

	if (BoxVisualAsset.Succeeded())
	{
		MeshComp->SetStaticMesh(BoxVisualAsset.Object);
		MeshComp->SetRelativeLocation(FVector(0.0f, 0.0f, 0.0f));
		MeshComp->SetWorldScale3D(FVector(1.0f));
	}

	MeshComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	RootComponent = MeshComp;

	InitialLifeSpan = 1.0f;

}

// Called when the game starts or when spawned
void ATestowyActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ATestowyActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

