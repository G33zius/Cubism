// Fill out your copyright notice in the Description page of Project Settings.

#include "CubieDoor.h"

// Sets default values
ACubieDoor::ACubieDoor()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	// PrimaryActorTick.bCanEverTick = false;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	// Root->PrimaryComponentTick.bCanEverTick = false;
	// Root->PrimaryComponentTick.bStartWithTickEnabled = false;
    RootComponent = Root;
	
	DoorMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("DoorMesh"));
    DoorMesh->SetupAttachment(Root);
	// DoorMesh->PrimaryComponentTick.bCanEverTick = false;
	// DoorMesh->PrimaryComponentTick.bStartWithTickEnabled = false;
	DoorMesh->SetRelativeScale3D(FVector(300.0f, 300.0f, 1.0f));
	DoorMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	DoorCollisionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("DoorCollisionBox"));
	DoorCollisionBox->SetupAttachment(Root);
	// DoorCollisionBox->PrimaryComponentTick.bCanEverTick = false;
	// DoorCollisionBox->PrimaryComponentTick.bStartWithTickEnabled = false;
	DoorCollisionBox->SetBoxExtent(FVector(1.0f, 1.0f, 1.0f));
	DoorCollisionBox->SetRelativeScale3D(FVector(200.0f, 200.0f, 100.0f));

}

// Called when the game starts or when spawned
void ACubieDoor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACubieDoor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

