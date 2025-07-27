// Fill out your copyright notice in the Description page of Project Settings.

#include "Cube.h"

// Sets default values
ACube::ACube()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
}

// Called when the game starts or when spawned
void ACube::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ACube::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ACube::GetAdjacentCoordinates(FVector _Coordinates, TArray<FVector>& AdjacentCoordinates)
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

void ACube::GetIndicesSetCubieCount(int& IndexX, int& IndexY, int& IndexZ)
{
	IndexX = FMath::CeilToInt(Dimensions.X - 1);
	IndexY = FMath::CeilToInt(Dimensions.Y - 1);
	IndexZ = FMath::CeilToInt(Dimensions.Z - 1);
	CubieCount = IndexX * IndexY * IndexZ;
}

void ACube::GetLocationFromCoordinates(FVector _Coordinates, FVector& Location)
{
	Location = _Coordinates * CubieSize;
}

ACubie* ACube::FindNextShiftCubie(TArray<FVector> AdjacentCoordinates, const FVector NullLocation, const bool Debug)
{
	const FVector TraceStart = NullLocation;
	constexpr float TraceLength = 500000;
	LineTraceForShiftCubie(TraceStart, TraceStart + GetActorForwardVector() * TraceLength, Debug);
	LineTraceForShiftCubie(TraceStart, TraceStart + GetActorForwardVector() * TraceLength * -1, Debug);
	LineTraceForShiftCubie(TraceStart, TraceStart + GetActorUpVector() * TraceLength, Debug);
	LineTraceForShiftCubie(TraceStart, TraceStart + GetActorUpVector() * TraceLength * -1, Debug);
	LineTraceForShiftCubie(TraceStart, TraceStart + GetActorRightVector() * TraceLength, Debug);
	LineTraceForShiftCubie(TraceStart, TraceStart + GetActorRightVector() * TraceLength * -1, Debug);
	
	if (NullAdjacentCubies.Num() > 0) {
		Algo::RandomShuffle(NullAdjacentCubies);
		for (AActor* Actor : NullAdjacentCubies)
		{
			ACubie* ShiftCubie = Cast<ACubie>(Actor);
			if (ShiftCubie != nullptr && !ShiftCubie->IsCenterCubie && !ShiftCubie->IsExitCubie && !ShiftCubie->IsEntranceCubie  && !ShiftCubie->IsPlayerCubie && !ShiftCubie->IsActivePathCubie){
				if (!ShiftCubie->HasMoved ) {
					for (const FVector& Adjacent : AdjacentCoordinates)
					{
						if (Adjacent == ShiftCubie->Coordinates)
						{
							NullAdjacentCubies.Empty();
							return ShiftCubie;
						}
					}
				}
			}
		}
	}
	NullAdjacentCubies.Empty();
	return nullptr;
}

void ACube::LineTraceForShiftCubie(const FVector StartLocation, const FVector EndLocation, const bool Debug)
{
	FHitResult Hit;
	FCollisionQueryParams QueryParams;
	QueryParams.AddIgnoredActor(this);
	GetWorld()->LineTraceSingleByProfile(Hit, StartLocation, EndLocation, TEXT("CubieTrace"), QueryParams);
	if (Debug) {
		constexpr float LifeTime = 0.3f;
		constexpr float LineThickness = 100.0f;
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
		NullAdjacentCubies.AddUnique(Hit.GetActor());
		//UE_LOG(LogTemp, Log, TEXT("Trace hit actor: %s"), *Hit.GetActor()->GetName());
	}
	else
	{
		//UE_LOG(LogTemp, Log, TEXT("No Actors were hit"));
	}
}

AActor* ACube::LineTraceForCubieGeneric(const FVector StartLocation, const FVector EndLocation, const bool Debug)
{
	FHitResult Hit;
	// float LifeTime = 0.3f;
	// float LineThickness = 10.0f;
	FCollisionQueryParams QueryParams;
	QueryParams.AddIgnoredActor(this);
	GetWorld()->LineTraceSingleByProfile(Hit, StartLocation, EndLocation, TEXT("CubieTrace"), QueryParams);
	if (Hit.bBlockingHit && IsValid(Hit.GetActor())) {
		return Hit.GetActor();
	}
	return nullptr;
}
