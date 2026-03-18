// Fill out your copyright notice in the Description page of Project Settings.


#include "Trap.h"

// Sets default values
ATrap::ATrap()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	Root->PrimaryComponentTick.bCanEverTick = false;
	Root->PrimaryComponentTick.bStartWithTickEnabled = false;
    RootComponent = Root;

	TrapMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("TrapMesh"));
    TrapMesh->SetupAttachment(Root);
	TrapMesh->PrimaryComponentTick.bCanEverTick = false;
	TrapMesh->PrimaryComponentTick.bStartWithTickEnabled = false;

	TrapCollisionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("TrapCollisionBox"));
	TrapCollisionBox->SetupAttachment(Root);
	TrapCollisionBox->PrimaryComponentTick.bCanEverTick = false;
	TrapCollisionBox->PrimaryComponentTick.bStartWithTickEnabled = false;
	TrapCollisionBox->SetBoxExtent(FVector(1.0f, 1.0f, 1.0f));
	TrapCollisionBox->SetWorldScale3D(FVector(100.0f, 100.0f, 100.0f));

	// TrapEffect = CreateDefaultSubobject<UNiagaraComponent>(TEXT("TrapEffect"));
	// TrapEffect->SetupAttachment(Root);

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

void ATrap::GetDistanceToPlayer(float& DistanceToPlayer)
{
	ACubismCharacter* Player = nullptr;
	GetPlayer(Player);
	if (Player == nullptr){
		UE_LOG(LogTemp, Error, TEXT("ATrap::GetDistanceToPlayer - Player is null!"));
		DistanceToPlayer = 0.0f;
		return;
	}
	DistanceToPlayer = FVector::Dist(Player->GetActorLocation(), GetActorLocation());
}

void ATrap::GetPlayer(ACubismCharacter*& Player)
{
	ACubismCharacter* CubismCharacter = Cast<ACubismCharacter>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
	if(CubismCharacter == nullptr){
		Player = nullptr;
		return;
	}
    Player = CubismCharacter;
}

void ATrap::SetCalculatedDamageInverseSquare(float _DistanceToPlayer, float& CalculatedDamage)
{
	float InverseDistanceToPlayerSquared = 1 / FMath::Square(_DistanceToPlayer);
	float PreClampedDamage = BaseDamage * InverseDistanceToPlayerSquared * GetWorld()->GetDeltaSeconds();
	CalculatedDamage = FMath::Clamp(PreClampedDamage, 0.0f, 1.0f);
}
