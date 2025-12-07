// Fill out your copyright notice in the Description page of Project Settings.


#include "Trap.h"

// Sets default values
ATrap::ATrap()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
    RootComponent = Root;
	TrapMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("TrapMesh"));
    TrapMesh->SetupAttachment(Root);
	// TrapEffect = CreateDefaultSubobject<UNiagaraComponent>(TEXT("TrapEffect"));
	// TrapEffect->SetupAttachment(Root);
	TrapCollisionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("TrapCollisionBox"));
	TrapCollisionBox->SetupAttachment(Root);
	TrapCollisionBox->SetBoxExtent(FVector(1.0f, 1.0f, 1.0f));
	TrapCollisionBox->SetWorldScale3D(FVector(100.0f, 100.0f, 100.0f));
	
}

// Called when the game starts or when spawned
void ATrap::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ATrap::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

