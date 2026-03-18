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

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	Root->PrimaryComponentTick.bCanEverTick = false;
	Root->PrimaryComponentTick.bStartWithTickEnabled = false;
	RootComponent = Root;

	DebugCubieMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("DebugCubieMeshComponent"));
    DebugCubieMeshComponent->SetupAttachment(Root);
	DebugCubieMeshComponent->PrimaryComponentTick.bCanEverTick = false;
	DebugCubieMeshComponent->PrimaryComponentTick.bStartWithTickEnabled = false;
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

void ACubie::UpdateOxygen(float Change)
{
	RoomOxygen += Change;
}

void ACubie::SpawnKineticCubes(bool bDoSpawn)
{
	if (bDoSpawn){
		// UNiagaraFunctionLibrary::SpawnSystemAttached(
	}
}

void ACubie::SpawnCubiePanels(bool bDoSpawn)
{
	if (bDoSpawn){
		for (const FTransform& CubiePanelTransform : CubiePanelTransforms){
			UStaticMeshComponent* NewMeshComponent = NewObject<UStaticMeshComponent>(this);
			if (NewMeshComponent){
				if (CubiePanelMesh){
					NewMeshComponent->SetStaticMesh(CubiePanelMesh);
					NewMeshComponent->RegisterComponent();
					NewMeshComponent->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
					NewMeshComponent->SetWorldTransform(CubiePanelTransform);
					NewMeshComponent->SetGenerateOverlapEvents(false);
					NewMeshComponent->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
					NewMeshComponent->SetCollisionObjectType(ECollisionChannel::ECC_WorldStatic);
					NewMeshComponent->SetCollisionProfileName(TEXT("CubieFrame"));
					NewMeshComponent->SetCollisionResponseToChannel(ECollisionChannel::ECC_GameTraceChannel1, ECollisionResponse::ECR_Block);
					NewMeshComponent->SetMobility(EComponentMobility::Movable);
				}else{
					UE_LOG(LogTemp, Warning, TEXT("BP_Cubie->CubiePanelMesh is not set!"));
				}
			}
		}
	}
}

void ACubie::SpawnKineticCubeWalls(bool bDoSpawn)
{
	
}

void ACubie::CacheCubieVisuals()
{
	DMI_Cubie->GetVectorParameterValue(FName("Color"), LastColor);
	DMI_Cubie->GetScalarParameterValue(FName("Emissive"), LastCubieEmissive);
}

void ACubie::RestoreCubieVisuals()
{
	// cache current color and emissive
	FLinearColor TempColor;
	DMI_Cubie->GetVectorParameterValue(FName("Color"), TempColor);
	float TempEmissive;
	DMI_Cubie->GetScalarParameterValue(FName("Emissive"), TempEmissive);
	// restore last color and emissive
	DMI_Cubie->SetVectorParameterValue(FName("Color"), LastColor);
	DMI_Cubie->SetScalarParameterValue(FName("Emissive"), LastCubieEmissive);
	// set last color and emissive to cached values
	LastColor = TempColor;
	LastCubieEmissive = TempEmissive;
}

void ACubie::PressCenterCubieSwitch()
{
	if (ParentCube == nullptr){
		UE_LOG(LogTemp, Error, TEXT("ACubie::PressCenterCubieSwitch - ParentCube is null!"));
		return;
	}
	if(bIsCenterCubie && !ParentCube->bCenterCubieSwitchPressed){
		ParentCube->bCenterCubieSwitchPressed = true;
		ParentCube->SetExitCubie();
	}
}

void ACubie::GetRandomCubiePickChance(bool bDebug, float DebugDuration)
{
	if (ParentCube == nullptr){
		UE_LOG(LogTemp, Error, TEXT("ACubie::GetRandomCubiePickChance - ParentCube is null!"));
		return;
	}
	if (!bIsTestCubie){
		float DistanceToDestinationCubie;
		ParentCube->GetDistanceToDestinationCubie(DistanceToDestinationCubie);
		DistanceToDestination = FMath::Clamp(DistanceToDestinationCubie, 0.0f, ParentCube->MaxDistanceToDestination);
		RandomChanceOfCubiePick = FMath::Clamp((1.0f - ((DistanceToDestination / ParentCube->MaxDistanceToDestination) - 0.1f)), 0.0f, 1.0f);
		if (RandomChanceOfCubiePick < FMath::RandRange(0.0f, 1.0f)){
			bIsBestPathSelected = true;
		}
	}
}

bool ACubie::DeriveCanDespawn(bool bDebug, float DebugDuration)
{
	if (ParentCube == nullptr){
		UE_LOG(LogTemp, Error, TEXT("ACubie::DeriveCanDespawn - ParentCube is null!"));
		return false;
	}
	bCanDespawn = true;
	if(ParentCube->PlayerCubie == this){
		bCanDespawn = false;
		if (bDebug){
			// UKismetSystemLibrary::PrintString(this, TEXT("Cannot Despawn: Player Cubie"), true, true, FLinearColor::Red, DebugDuration);
		}
		return bCanDespawn;
	}
	AdjacentCubies = GetAdjacentCubies(bDebug);
	for (AActor* Actor : AdjacentCubies){
		ACubie* AdjacentCubie = Cast<ACubie>(Actor);
		if (AdjacentCubie != nullptr){
			if (AdjacentCubie == this){
				bCanDespawn = false;
				if (bDebug){
					// UKismetSystemLibrary::PrintString(this, TEXT("Cannot Despawn: Adjacent to Player Cubie"), true, true, FLinearColor::Red, DebugDuration);
				}
				return bCanDespawn;
			}
		}
	}
	return bCanDespawn;
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

TArray<AActor*> ACubie::GetAdjacentCubies(const bool bDebug){
	FVector StartLocation;
	GetLocationFromCoordinates(Coordinates, StartLocation);
	constexpr float TraceLength = 500000;
	LineTraceForAdjacentCubie(StartLocation, StartLocation + GetActorForwardVector() * TraceLength, bDebug);
	LineTraceForAdjacentCubie(StartLocation, StartLocation + GetActorForwardVector() * TraceLength * -1, bDebug);
	LineTraceForAdjacentCubie(StartLocation, StartLocation + GetActorUpVector() * TraceLength, bDebug);
	LineTraceForAdjacentCubie(StartLocation, StartLocation + GetActorUpVector() * TraceLength * -1, bDebug);
	LineTraceForAdjacentCubie(StartLocation, StartLocation + GetActorRightVector() * TraceLength, bDebug);
	LineTraceForAdjacentCubie(StartLocation, StartLocation + GetActorRightVector() * TraceLength * -1, bDebug);
	return AdjacentCubies;
}

void ACubie::LineTraceForAdjacentCubie(const FVector StartLocation, const FVector EndLocation, const bool bDebug)
{
	FHitResult Hit;
	FCollisionQueryParams QueryParams;
	QueryParams.AddIgnoredActor(this);
	GetWorld()->LineTraceSingleByProfile(Hit, StartLocation, EndLocation, TEXT("CubieTrace"), QueryParams);
	if (bDebug){
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

	if (Hit.bBlockingHit && IsValid(Hit.GetActor())){
		AdjacentCubies.AddUnique(Hit.GetActor());
		//UE_LOG(LogTemp, Log, TEXT("Trace hit actor: %s"), *Hit.GetActor()->GetName());
	}else{
		//UE_LOG(LogTemp, Log, TEXT("No Actors were hit"));
	}
}

ACubie* ACubie::FindNextPathCubie(const bool bDebug)
{
	FVector StartLocation;
	GetLocationFromCoordinates(Coordinates, StartLocation);
	constexpr float TraceLength = 500000;
	LineTraceForPathCubie(StartLocation, StartLocation + GetActorForwardVector() * TraceLength, bDebug);
	LineTraceForPathCubie(StartLocation, StartLocation + GetActorForwardVector() * TraceLength * -1, bDebug);
	LineTraceForPathCubie(StartLocation, StartLocation + GetActorUpVector() * TraceLength, bDebug);
	LineTraceForPathCubie(StartLocation, StartLocation + GetActorUpVector() * TraceLength * -1, bDebug);
	LineTraceForPathCubie(StartLocation, StartLocation + GetActorRightVector() * TraceLength, bDebug);
	LineTraceForPathCubie(StartLocation, StartLocation + GetActorRightVector() * TraceLength * -1, bDebug);
	if (PathAdjacentCubies.Num() > 0){
		Algo::RandomShuffle(PathAdjacentCubies);
		for (AActor* Actor : PathAdjacentCubies){
			ACubie* PathCubie = Cast<ACubie>(Actor);
			if (PathCubie != nullptr && !PathCubie->bIsPathCubie){
				PathAdjacentCubies.Empty();
				return PathCubie;
			}
		}
		PathAdjacentCubies.Empty();
	}
	return nullptr;
}

void ACubie::LineTraceForPathCubie(const FVector StartLocation, const FVector EndLocation, const bool bDebug)
{
	FHitResult Hit;
	FCollisionQueryParams QueryParams;
	QueryParams.AddIgnoredActor(this);
	GetWorld()->LineTraceSingleByProfile(Hit, StartLocation, EndLocation, TEXT("CubieTrace"), QueryParams);
	if (bDebug){
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
	
	if (Hit.bBlockingHit && IsValid(Hit.GetActor())){
		PathAdjacentCubies.AddUnique(Hit.GetActor());
		//UE_LOG(LogTemp, Log, TEXT("Trace hit actor: %s"), *Hit.GetActor()->GetName());
	}else {
		//UE_LOG(LogTemp, Log, TEXT("No Actors were hit"));
	}
}

ACubie* ACubie::BoxFindNextPathToCubie(FVector const EndCoordinates, const bool bDebug)
{
	FVector StartLocation;
	FVector EndLocation;
	GetLocationFromCoordinates(Coordinates, StartLocation);
	GetLocationFromCoordinates(EndCoordinates, EndLocation);
	BoxTraceForPathCubie(StartLocation, EndLocation, bDebug);

	if (PathAdjacentCubies.Num() > 0){
		//Algo::RandomShuffle(PathAdjacentCubies);
		for (AActor* Actor : PathAdjacentCubies){
			ACubie* PathCubie = Cast<ACubie>(Actor);
			if (PathCubie != nullptr && !PathCubie->bIsPathCubie){
				PathAdjacentCubies.Empty();
				return PathCubie;
			}
		}
		PathAdjacentCubies.Empty();
	}
	return nullptr;
}

void ACubie::BoxTraceForPathCubie(const FVector StartLocation, const FVector EndLocation, const bool bDebug)
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
	if (bDebug){
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

	if (OutHit.bBlockingHit && IsValid(OutHit.GetActor())){
		PathAdjacentCubies.AddUnique(OutHit.GetActor());
	}else {
		//UE_LOG(LogTemp, Log, TEXT("No Actors were hit"));
	}
}

void ACubie::DestroyActorsByArray(TArray<AActor*> Actors)
{
	for (AActor* Actor : Actors){
		if (Actor != nullptr){
			GetWorld()->DestroyActor(Actor);
		}
	}
	Actors.Empty();
}


void ACubie::DestroyActorComponentsByArray(TArray<UActorComponent*> ActorComponents)
{
	for (UActorComponent* ActorComponent : ActorComponents){
		if (ActorComponent != nullptr){
			ActorComponent->DestroyComponent();
		}
	}
	ActorComponents.Empty();
}

void ACubie::DestroyChildActorComponentsByArray(TArray<UChildActorComponent*> ChildActorComponents)
{
	for (UChildActorComponent* ChildActorComponent : ChildActorComponents){
		if (ChildActorComponent != nullptr){
			ChildActorComponent->DestroyComponent();
		}
	}
	ChildActorComponents.Empty();
}

void ACubie::GetPlayer(ACubismCharacter*& Player)
{
	ACubismCharacter* CubismCharacter = Cast<ACubismCharacter>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
	if(CubismCharacter == nullptr){
		Player = nullptr;
		return;
	}
    Player = CubismCharacter;
}