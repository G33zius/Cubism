// Fill out your copyright notice in the Description page of Project Settings.


#include "Cubie.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Kismet/KismetMathLibrary.h"
#include "Cube.h"

// Sets default values
ACubie::ACubie()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
}

// Called when the game starts or when spawned
void ACubie::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ACubie::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ACubie::GetLocationFromCoordinates(FVector _Coordinates, FVector& Location)
{
	Location = _Coordinates * CubieSize;
}

void ACubie::LerpToLocation(const FVector NewLocation, const float Alpha)
{
	SetActorLocation(FMath::Lerp(GetActorLocation(), NewLocation, Alpha));
}

void ACubie::UpdateCoordinatesFromShift(FVector _LastCoordinates, FVector LastNullCoordinates, FVector& NewCoordinates, FVector& NewNullCoordinates)
{
	Coordinates = LastNullCoordinates;
	LastCoordinates = _LastCoordinates;
	NewNullCoordinates = _LastCoordinates;
	NewCoordinates = LastNullCoordinates;
}

void ACubie::GetAdjacentCoordinates(FVector _Coordinates, TArray<FVector>& AdjacentCoordinates)
{
	FVector NextCoordinates = FVector(_Coordinates.X + 1.0f, _Coordinates.Y, _Coordinates.Z);
	AdjacentCoordinates.Add(NextCoordinates);
	NextCoordinates = FVector(_Coordinates.X - 1.0f, _Coordinates.Y, _Coordinates.Z);
	AdjacentCoordinates.Add(NextCoordinates);
	NextCoordinates = FVector(_Coordinates.X, _Coordinates.Y + 1.0f, _Coordinates.Z);
	AdjacentCoordinates.Add(NextCoordinates);
	NextCoordinates = FVector(_Coordinates.X, _Coordinates.Y - 1.0f, _Coordinates.Z);
	AdjacentCoordinates.Add(NextCoordinates);
	NextCoordinates = FVector(_Coordinates.X, _Coordinates.Y, _Coordinates.Z + 1.0f);
	AdjacentCoordinates.Add(NextCoordinates);
	NextCoordinates = FVector(_Coordinates.X, _Coordinates.Y, _Coordinates.Z - 1.0f);
	AdjacentCoordinates.Add(NextCoordinates);
}

ACubie* ACubie::FindNextPathCubie(const bool Debug)
{
	FVector StartLocation;
	GetLocationFromCoordinates(Coordinates, StartLocation);
	constexpr float TraceLength = 500000;
	LineTraceForPathCubie(StartLocation, StartLocation + GetActorForwardVector() * TraceLength, Debug);
	LineTraceForPathCubie(StartLocation, StartLocation + GetActorForwardVector() * TraceLength * -1, Debug);
	LineTraceForPathCubie(StartLocation, StartLocation + GetActorUpVector() * TraceLength, Debug);
	LineTraceForPathCubie(StartLocation, StartLocation + GetActorUpVector() * TraceLength * -1, Debug);
	LineTraceForPathCubie(StartLocation, StartLocation + GetActorRightVector() * TraceLength, Debug);
	LineTraceForPathCubie(StartLocation, StartLocation + GetActorRightVector() * TraceLength * -1, Debug);

	if (PathAdjacentCubies.Num() > 0) {
		Algo::RandomShuffle(PathAdjacentCubies);
		for (AActor* Actor : PathAdjacentCubies)
		{
			ACubie* PathCubie = Cast<ACubie>(Actor);
			if (PathCubie != nullptr && !PathCubie->IsPathCubie) {
				PathAdjacentCubies.Empty();
				return PathCubie;
			}
		}
		PathAdjacentCubies.Empty();
	}
	return nullptr;
}

void ACubie::LineTraceForPathCubie(const FVector StartLocation, const FVector EndLocation, const bool Debug)
{
	FHitResult Hit;
	FCollisionQueryParams QueryParams;
	QueryParams.AddIgnoredActor(this);
	GetWorld()->LineTraceSingleByProfile(Hit, StartLocation, EndLocation, TEXT("CubieTrace"), QueryParams);
	if (Debug) {
		constexpr float LifeTime = 0.2f;
		constexpr float LineThickness = 10.0f;
		DrawDebugLine(
			GetWorld(),
			StartLocation,
			EndLocation,
			Hit.bBlockingHit ? FColor::Red : FColor::Green,
			false,
			LifeTime,
			0,
			LineThickness
			);
	}
	
	if (Hit.bBlockingHit && IsValid(Hit.GetActor()))
	{
		PathAdjacentCubies.AddUnique(Hit.GetActor());
		//UE_LOG(LogTemp, Log, TEXT("Trace hit actor: %s"), *Hit.GetActor()->GetName());
	}
	else
	{
		//UE_LOG(LogTemp, Log, TEXT("No Actors were hit"));
	}
}

ACubie* ACubie::BoxFindNextPathToCubie(const bool Debug, FVector const EndCoordinates)
{
	FVector StartLocation;
	FVector EndLocation;
	GetLocationFromCoordinates(Coordinates, StartLocation);
	GetLocationFromCoordinates(EndCoordinates, EndLocation);
	BoxTraceForPathCubie(StartLocation, EndLocation, Debug);

	if (PathAdjacentCubies.Num() > 0)
	{
		//Algo::RandomShuffle(PathAdjacentCubies);
		for (AActor* Actor : PathAdjacentCubies)
		{
			ACubie* PathCubie = Cast<ACubie>(Actor);
			if (PathCubie != nullptr && !PathCubie->IsPathCubie)
			{
				PathAdjacentCubies.Empty();
				return PathCubie;
			}
		}
		PathAdjacentCubies.Empty();
	}
	return nullptr;
}

void ACubie::BoxTraceForPathCubie(const FVector StartLocation, const FVector EndLocation, const bool Debug)
{
	//TArray<FHitResult> OutHits;
	constexpr float LifeTime = 1.0f;
	// constexpr float LineThickness = 10.0f;
	// FCollisionQueryParams QueryParams;
	// QueryParams.AddIgnoredActor(this);
	// FCollisionShape SweepShape = FCollisionShape::MakeBox(FVector(10.0f));
	FVector Direction = (EndLocation - StartLocation).GetSafeNormal();
	Direction.Normalize();
	TArray<TEnumAsByte<EObjectTypeQuery>> ObjectTypes;
	ObjectTypes.Add(UEngineTypes::ConvertToObjectType(ECollisionChannel::ECC_GameTraceChannel1));
	TArray<AActor*> ActorsToIgnore;
	ActorsToIgnore.Init(this, 1);
	FHitResult OutHit;
	EDrawDebugTrace::Type DrawDebugType = EDrawDebugTrace::None;

	//GetWorld()->SweepMultiByChannel(OutHits, StartLocation, Direction * 100, FQuat::Identity, ECC_GameTraceChannel2, SweepShape, QueryParams);
	if (Debug) {
		DrawDebugType = EDrawDebugTrace::ForDuration;
	}
	UKismetSystemLibrary::BoxTraceSingleByProfile(
		GetWorld(),
		StartLocation,
		EndLocation, //Direction * 100,
		FVector(50.0f),
		UKismetMathLibrary::FindLookAtRotation(StartLocation, EndLocation),
		TEXT("CubieTrace"),
		false,
		ActorsToIgnore,
		DrawDebugType,
		OutHit,
		true,
		FColor::Cyan,
		FColor::Red,
		LifeTime
		);
	
	if (OutHit.bBlockingHit && IsValid(OutHit.GetActor()))
	{
		PathAdjacentCubies.AddUnique(OutHit.GetActor());
	}
	else
	{
		//UE_LOG(LogTemp, Log, TEXT("No Actors were hit"));
	}
}

void ACubie::DeleteComponents(TArray<UActorComponent*> ActorComponents)
{
	for (UActorComponent* ActorComponent : ActorComponents) {
		if (ActorComponent)
		{
			ActorComponent->DestroyComponent();
		}
	}
	ActorComponents.Empty();
}

void ACubie::DeleteChildActorComponents(TArray<UChildActorComponent*> ChildActorComponents)
{
for (UActorComponent* ChiildActorComponent : ChildActorComponents) {
	if (ChiildActorComponent)
		{
			ChiildActorComponent->DestroyComponent();
		}
		}
		ChildActorComponents.Empty();
	}