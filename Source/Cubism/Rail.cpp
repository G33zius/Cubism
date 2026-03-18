// Fill out your copyright notice in the Description page of Project Settings.


#include "Rail.h"

// Sets default values
ARail::ARail()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	Root->PrimaryComponentTick.bCanEverTick = false;
	Root->PrimaryComponentTick.bStartWithTickEnabled = false;
	Root->PrimaryComponentTick.bStartWithTickEnabled = false;
    RootComponent = Root;

	RailMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("RailMesh"));
    RailMesh->SetupAttachment(Root);
	RailMesh->PrimaryComponentTick.bCanEverTick = false;
	RailMesh->PrimaryComponentTick.bStartWithTickEnabled = false;
	RailMesh->SetWorldScale3D(FVector(5.0f, 5.0f, 2400.0f));
	RailMesh->SetWorldLocation(FVector(10.0f, 0.0f, 0.0f));
	RailMesh->SetCollisionProfileName(TEXT("NoCollision"));
	

	RailCollisionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("RailCollisionBox"));
	RailCollisionBox->SetupAttachment(Root);
	RailCollisionBox->PrimaryComponentTick.bCanEverTick = false;
	RailCollisionBox->PrimaryComponentTick.bStartWithTickEnabled = false;
	RailCollisionBox->SetBoxExtent(FVector(1.0f, 1.0f, 1.0f));
	RailCollisionBox->SetWorldScale3D(FVector(RailThickness, RailWidth, RailLength));
	RailCollisionBox->SetCollisionProfileName(TEXT("OverlapAllDynamic"));
	RailCollisionBox->CanCharacterStepUpOn = ECanBeCharacterBase::ECB_No;

	RectLight = CreateDefaultSubobject<URectLightComponent>(TEXT("RectLight"));
	RectLight->SetupAttachment(Root);
	RectLight->PrimaryComponentTick.bCanEverTick = false;
	RectLight->PrimaryComponentTick.bStartWithTickEnabled = false;
	RectLight->SetWorldLocation(FVector(5.0f, 0.0f, 0.0f));
	RectLight->SetIntensity(8.0f);
	RectLight->AttenuationRadius = 2400.0f;
	RectLight->SourceWidth = 10.0f;
	RectLight->SourceHeight = 2400.0f;
	RectLight->BarnDoorAngle = 0.0f;
	RectLight->BarnDoorLength = 10.0f;
	// RectLight->MegaLightsShadowMethod = EMegaLightsShadowMethod::RayTraced;
}

// Called when the game starts or when spawned
void ARail::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ARail::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

