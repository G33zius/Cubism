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

ACubie* ACube::FindNextShiftCubie(TArray<FVector> AdjacentCoordinates, const FVector NullLocation, const bool bDebug)
{
	const FVector TraceStart = NullLocation;
	constexpr float TraceLength = 500000;
	LineTraceForShiftCubie(TraceStart, TraceStart + GetActorForwardVector() * TraceLength, bDebug);
	LineTraceForShiftCubie(TraceStart, TraceStart + GetActorForwardVector() * TraceLength * -1, bDebug);
	LineTraceForShiftCubie(TraceStart, TraceStart + GetActorUpVector() * TraceLength, bDebug);
	LineTraceForShiftCubie(TraceStart, TraceStart + GetActorUpVector() * TraceLength * -1, bDebug);
	LineTraceForShiftCubie(TraceStart, TraceStart + GetActorRightVector() * TraceLength, bDebug);
	LineTraceForShiftCubie(TraceStart, TraceStart + GetActorRightVector() * TraceLength * -1, bDebug);
	
	if (NullAdjacentCubies.Num() > 0) {
		// UE_LOG(LogTemp, Warning, TEXT("ACube::FindNextShiftCubie - %d Adjacent Cubies were found"), NullAdjacentCubies.Num());
		Algo::RandomShuffle(NullAdjacentCubies);
		for (ACubie* NullAdjacentCubie : NullAdjacentCubies){
			if (NullAdjacentCubie != nullptr && NullAdjacentCubie != CubieToLoad && !NullAdjacentCubie->bIsCenterCubie && !NullAdjacentCubie->bIsExitCubie && !NullAdjacentCubie->bIsEntranceCubie  && !NullAdjacentCubie->bIsPlayerCubie && !NullAdjacentCubie->bIsActivePathCubie){
				// UE_LOG(LogTemp, Warning, TEXT("ACube::FindNextShiftCubie - NullAdjacentCubie was NOT filtered out"));
				if (!NullAdjacentCubie->bHasMoved) {
					// UE_LOG(LogTemp, Warning, TEXT("ACube::FindNextShiftCubie - NullAdjacentCubie NOT already moved"));
					for (const FVector& AdjacentCoordinate : AdjacentCoordinates) {
						if (AdjacentCoordinate == NullAdjacentCubie->Coordinates) {
							UE_LOG(LogTemp, Warning, TEXT("ACube::FindNextShiftCubie - Coordinates match found: %s"), *AdjacentCoordinate.ToString());
							NullAdjacentCubies.Empty();
							return NullAdjacentCubie;
						}
						else{
							UE_LOG(LogTemp, Warning, TEXT("ACube::FindNextShiftCubie - Coordinates match NOT found - Adj:%s vs NullAdj:%s"), *AdjacentCoordinate.ToString(), *NullAdjacentCubie->Coordinates.ToString());
						}
					}
				}
			}
		}
	}else{
		UE_LOG(LogTemp, Warning, TEXT("ACube::FindNextShiftCubie - No Null Adjacent Cubies were found"));
	}
	return nullptr;
}

void ACube::LineTraceForShiftCubie(const FVector StartLocation, const FVector EndLocation, const bool bDebug)
{
	FHitResult Hit;
	FCollisionQueryParams QueryParams;
	QueryParams.AddIgnoredActor(this);
	GetWorld()->LineTraceSingleByProfile(Hit, StartLocation, EndLocation, TEXT("CubieTrace"), QueryParams);
	if (bDebug) {
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
	if (Hit.bBlockingHit && IsValid(Hit.GetActor())){
		NullAdjacentCubies.AddUnique(Cast<ACubie>(Hit.GetActor()));
		UE_LOG(LogTemp, Log, TEXT("ACube::LineTraceForShiftCubie - Trace hit actor: %s"), *Hit.GetActor()->GetName());
	} else {
		UE_LOG(LogTemp, Log, TEXT("ACube::LineTraceForShiftCubie - No Actors were hit"));
	}
}

AActor* ACube::LineTraceForCubieGeneric(const FVector StartLocation, const FVector EndLocation, const bool bDebug)
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

void ACube::BuildCubieGrid()
{
	int IndexX;
	int IndexY;
	int IndexZ;
	GetIndicesSetCubieCount(IndexX, IndexY, IndexZ);
	Coordinates.Empty();
	for (int x = 0; x <= IndexX; x++) {
		for (int y = 0; y <= IndexY; y++) {
			for (int z = 0; z <= IndexZ; z++) {
				Coordinates.Add(FVector(x, y, z));
			}
		}
	}
	PrepCoordinatesArray();
	DrawDebugBox(GetWorld(), GetActorLocation(), FVector(Dimensions.X / 2.0f, Dimensions.Y  / 2.0f, Dimensions.Z / 2.0f) * CubieSize, FColor::FromHex("#97002EFF"), false, 999.0f, 0, 50.0f);
}

void ACube::PrepCoordinatesArray()
{
	// Sort in Reverse
	Coordinates.Sort([](const FVector& A, const FVector& B) {
		if (A.X != B.X) {
			return A.X > B.X;
		}
		else if (A.Y != B.Y) {
			return A.Y > B.Y;
		}
		else {
			return A.Z > B.Z;
		}
		});
	NullCoordinates = Coordinates[0];
}

void ACube::GetDistanceToDestinationCubie(float& DistanceToDestinationCubie)
{
	if (DestinationCubie && PlayerCubie) {
		DistanceToDestinationCubie = FVector::Dist(PlayerCubie->GetActorLocation(), DestinationCubie->GetActorLocation());
	}
}

void ACube::GetRandomInitialEdgeCubie(ACubie *&EdgeCubie)
{
	EdgeCubie = nullptr;
	if (InitialEdgeCubies.Num() > 0) {
		Algo::RandomShuffle(InitialEdgeCubies);
		EdgeCubie = InitialEdgeCubies[0];
	}
}

void ACube::ResetMovedFlags()
{
	for (ACubie* Cubie : AllCubies) {
		if (Cubie) {
			Cubie->bHasMoved = false;
		}
	}
	MovedCount = 0;
}

void ACube::SpawnCubie(FVector _Coordinates)
{
	FVector Location;
	GetLocationFromCoordinates(_Coordinates, Location);
	FActorSpawnParameters SpawnParams;
        SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	ACubie* NewCubie = GetWorld()->SpawnActor<ACubie>(ACubie::StaticClass(), Location, FRotator::ZeroRotator, SpawnParams);
	if (NewCubie) {
		NewCubie->CubieSize = CubieSize;
		NewCubie->LastCoordinates = _Coordinates;
		NewCubie->Coordinates = _Coordinates;
		if(CheckEdgeCubieByCoordinates(_Coordinates)) {
			NewCubie->bIsEdgeCubie = true;
			NewCubie->RectLightColor = Yellow;
			if(NewCubie->DMI_Cubie) {
				NewCubie->DMI_Cubie->SetVectorParameterValue(FName("Color"), FVector(Yellow));
				NewCubie->DMI_Cubie->SetScalarParameterValue(FName("Emissive"), NonPrimaryCubieEmissive);
			}else{
				UE_LOG(LogTemp, Warning, TEXT("NewCubie DMI_Cubie is null"));
			}
			InitialEdgeCubies.AddUnique(NewCubie);
		}
		else{
			NewCubie->RectLightColor = Orange;
			if(NewCubie->DMI_Cubie) {
				NewCubie->DMI_Cubie->SetVectorParameterValue(FName("Color"), FVector(Orange));
				NewCubie->DMI_Cubie->SetScalarParameterValue(FName("Emissive"), NonPrimaryCubieEmissive);
			}else{
				UE_LOG(LogTemp, Warning, TEXT("NewCubie DMI_Cubie is null"));
			}
		}
		AllCubies.AddUnique(NewCubie);
	}
}

bool ACube::CheckEdgeCubieByCoordinates(FVector _Coordinates)
{
	if (_Coordinates.X == 0.0f || 
		_Coordinates.Y == 0.0f || 
		_Coordinates.Z == 0.0f ||
		_Coordinates.X == Dimensions.X - 1.0f ||
		_Coordinates.Y == Dimensions.Y - 1.0f ||
		_Coordinates.Z == Dimensions.Z - 1.0f) {
		return true;
	}
	return false;
}

void ACube::SetCenterCubie(const bool bDebug, const float DebugDuration, const FLinearColor DebugColor)
{
	FVector StartLocation = CubieSize * FVector((float)FMath::Floor(Dimensions.X / 2.0f), (float)FMath::Floor(Dimensions.Y / 2.0f), (float)FMath::Floor(Dimensions.Z / 2.0f));
	FVector EndLocation = StartLocation + FVector(4000.0f, 4000.0f, 4000.0f);
	AActor* HitActor = LineTraceForCubieGeneric(StartLocation, EndLocation, bDebug);
	CenterCubie = Cast<ACubie>(HitActor);
	if (CenterCubie) {
		DestinationCubie = CenterCubie;
		CenterCubie->RectLightColor = Teal;
		if(CenterCubie->DMI_Cubie) {
			CenterCubie->DMI_Cubie->SetVectorParameterValue(FName("Color"), FVector(Teal));
			CenterCubie->DMI_Cubie->SetScalarParameterValue(FName("Emissive"), PrimaryCubieEmissive);
		}else{
			UE_LOG(LogTemp, Warning, TEXT("CenterCubie DMI_Cubie is null"));
		}
		CenterCubie->bIsActivePathCubie = false;
		CenterCubie->bIsPathCubie = true;
		CenterCubie->bIsCenterCubie = true;
		// if (bDebug) {
		// 	UE_LOG(LogTemp, Log, TEXT("Destination/Center Cubie: %f"), CenterCubie);
		// }
	}
}

void ACube::SetEntranceCubie(const bool bDebug, const float DebugDuration, const FLinearColor DebugColor)
{
	ACubie* _EntranceCubie = nullptr;
	GetRandomInitialEdgeCubie(_EntranceCubie);
	if(_EntranceCubie){
		EntranceCubie = _EntranceCubie;
		EntranceCubie->RectLightColor = Green;
		if(EntranceCubie->DMI_Cubie) {
			EntranceCubie->DMI_Cubie->SetVectorParameterValue(FName("Color"), FVector(Green));
			EntranceCubie->DMI_Cubie->SetScalarParameterValue(FName("Emissive"), PrimaryCubieEmissive);
		}else{
			UE_LOG(LogTemp, Warning, TEXT("EntranceCubie DMI_Cubie is null"));
		}
		EntranceCubie->bIsPathCubie = true;
		EntranceCubie->bIsEntranceCubie = true;
		// if (bDebug) {
		// 	UE_LOG(LogTemp, Log, TEXT("Entrance Cubie: %f"), EntranceCubie);
		// }
	}
}

void ACube::SetExitCubie(const bool bDebug, const float DebugDuration, const FLinearColor DebugColor)
{
	ACubie* _ExitCubie = nullptr;
	GetRandomInitialEdgeCubie(_ExitCubie);
	if(_ExitCubie){
		ExitCubie = _ExitCubie;
		ExitCubie->RectLightColor = Purple;
		if(ExitCubie->DMI_Cubie) {
			ExitCubie->DMI_Cubie->SetVectorParameterValue(FName("Color"), FVector(Purple));
			ExitCubie->DMI_Cubie->SetScalarParameterValue(FName("Emissive"), PrimaryCubieEmissive);
		}else{
			UE_LOG(LogTemp, Warning, TEXT("ExitCubie DMI_Cubie is null"));
		}
		ExitCubie->bIsActivePathCubie = false;
		ExitCubie->bIsPathCubie = true;
		ExitCubie->bIsExitCubie = true;
		// if (bDebug) {
		// 	UE_LOG(LogTemp, Log, TEXT("Exit Cubie: %f"), ExitCubie);
		// }
	}
}

void ACube::SetPlayerCubie(ACubie* Cubie, const bool bDebug, const float DebugDuration, const FLinearColor DebugColor)
{
	if(Cubie){
		PlayerCubie = Cubie;
	}
}

void ACube::CheckAndDespawnCubies()
{
	for (ACubie* LoadedCubie : LoadedCubies){
		if(LoadedCubie){
			// TODO
		}
	}
}

void ACube::SetMaxDistanceToDestination(const bool bDebug, const float DebugDuration, const FLinearColor DebugColor)
{
	float DistanceToDestinationCubie;
	GetDistanceToDestinationCubie(DistanceToDestinationCubie);
	MaxDistanceToDestination = DistanceToDestinationCubie;
	if (bDebug) {
		UE_LOG(LogTemp, Log, TEXT("Max Distance to Destination Cubie: %f"), MaxDistanceToDestination);
	}
}

void ACube::SetPlayerStartLocation(const bool bDebug, const float DebugDuration, const FLinearColor DebugColor)
{
	FVector Offset = FVector(0.0f, 300.0f, 0.0f);
	APawn* PlayerPawn = GetWorld()->GetFirstPlayerController()->GetPawn();
	ACubismCharacter* PlayerCharacter = Cast<ACubismCharacter>(PlayerPawn);
	PlayerStartLocation = EntranceCubie->GetActorLocation() + Offset;
	PlayerPawn->SetActorLocation(PlayerStartLocation);
	SetMaxDistanceToDestination(bDebug, DebugDuration, DebugColor);
	PlayerCubie = EntranceCubie;
	EntranceCubie->bWasVisited = true;
	EntranceCubie->bIsAwaitingVisit = false;
	PlayerCharacter->CurrentCubie = EntranceCubie;
}