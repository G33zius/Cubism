// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/RectLightComponent.h"
#include "Algo/RandomShuffle.h"
#include "Cubie.generated.h"

class ADoor;
class ACube;
class ARail;

UCLASS()
class CUBISM_API ACubie : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACubie();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "zCubieData")
	FVector Coordinates = FVector();

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "zCubieData")
	bool HasMoved = false;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "zCubieData")
	bool IsCenterCubie = false;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "zCubieData")
	bool IsExitCubie = false;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "zCubieData")
	bool IsEntranceCubie = false;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "zCubieData")
	bool IsActivePathCubie = false;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "zCubieData")
	bool IsPlayerCubie = false;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "zCubieData")
	bool HasSafePath = false;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "zCubieData")
	bool IsBestPathSelected = false;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "zCubieData")
	bool IsAwaitingVisit = false;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "zCubieData")
	bool WasVisited = false;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "zCubieData")
	bool UseCubeColoring = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "zCubieData")
	bool IsTestCubie = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "zCubieData")
	int Seed = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "zCubieData")
	FLinearColor RectLightColor = FColor::FromHex("008EFFFF");

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "zCubieData")
	FLinearColor LastColor = FColor::White;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "zCubieData")
	float RectLightIntensity = 1000000.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "zCubieData")
	float RectLightAttenuationRad = 2150.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "zCubieData")
	float LastCubieEmissive = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "zCubieData")
	float RectLightBarnDoorLength = 3000.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "zCubieData")
	float RoomSaturation = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "zCubieData")
	float RoomOxygen = 1.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "zCubieData")
	int CubieStreamSeed = 0;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "zCubieData")
	int Int32Max = 2147483647;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "zCubieData")
	FVector PlayerStartLocation = FVector();

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "zCubieData")
	UMaterialInstanceDynamic* DMI_Cubie;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "zCubieData")
	UMaterialInstanceDynamic* DMI_Rail;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "zCubieData")
	UMaterialInstanceDynamic* DMI_Door;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "zCubeData")
	ACube* ParentCube;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "zPlayerData")
	APawn* PlayerPawn;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "zPlayerData")
	APlayerController* PlayerController;

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "zComponents")
	USceneComponent* Root;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "zComponents")
    UStaticMeshComponent* DebugCubieMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "zComponents")
	TArray<URectLightComponent*> RectLights;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "zComponents")
    TArray<UStaticMeshComponent*> CubiePanelMeshes;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "zComponents")
	TArray<ADoor*> Doors;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "zComponents")
	TArray<ARail*> Rails;

private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "zCubieData", meta = (AllowPrivateAccess = "true"))
	float CubieSize = 3000.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "zCubieData", meta = (AllowPrivateAccess = "true"))
	FVector LastCoordinates = FVector();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "zCubieData", meta = (AllowPrivateAccess = "true"))
	float RandomChanceOfCubiePick;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "zCubieData", meta = (AllowPrivateAccess = "true"))
	float DistanceToDestination;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "zCubieData", meta = (AllowPrivateAccess = "true"))
	float Damage;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "zCubieData", meta = (AllowPrivateAccess = "true"))
	bool IsPathCubie = false;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "zCubieData", meta = (AllowPrivateAccess = "true"))
	bool IsEdge = false;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "zCubieData", meta = (AllowPrivateAccess = "true"))
	TArray<AActor*> PathAdjacentCubies;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "zCubieData", meta = (AllowPrivateAccess = "true"))
	TArray<AActor*> AdjacentCubies;

	UPROPERTY(EditDefaultsOnly, Category = "zCollision")
	TEnumAsByte<ECollisionChannel> TraceChannelProperty = ECC_GameTraceChannel1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "zDebug", meta = (AllowPrivateAccess = "true"))
	float DebugBoxDuration = 0.5f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "zCubieData", meta = (AllowPrivateAccess = "true"))
	float RailOffsetPanel = 1190.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "zCubieData", meta = (AllowPrivateAccess = "true"))
	float RailOffsetDoor = 200.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "zCubieData", meta = (AllowPrivateAccess = "true"))
	float DoorOffset = 1225.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "zCubieData", meta = (AllowPrivateAccess = "true"))
	bool IsLoaded = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "zCubieData", meta = (AllowPrivateAccess = "true"))
	bool CanDespawn = false;

	// Functions
	
	UFUNCTION(BlueprintCallable)
	void GetLocationFromCoordinates(FVector _Coordinates, FVector& Location);

	UFUNCTION(BlueprintCallable)
	void LerpToLocation(const FVector NewLocation, const float Alpha);

	UFUNCTION(BlueprintCallable)
	void UpdateCoordinatesFromShift(FVector _LastCoordinates, FVector LastNullCoordinates, FVector& NewCoordinates, FVector& NewNullCoordinates);

	UFUNCTION(BlueprintCallable)
	void GetAdjacentCoordinates(FVector _Coordinates, TArray<FVector>& AdjacentCoordinates);

	UFUNCTION(BlueprintCallable)
	ACubie* FindNextPathCubie(const bool Debug);

	UFUNCTION(BlueprintCallable)
    TArray<AActor*> GetAdjacentCubies(const bool Debug);

	UFUNCTION(BlueprintCallable)
    void LineTraceForAdjacentCubie(const FVector StartLocation, const FVector EndLocation, const bool Debug);

    UFUNCTION(BlueprintCallable)
	ACubie* BoxFindNextPathToCubie(const bool Debug, FVector const EndCoordinates);

	UFUNCTION(BlueprintCallable)
	void LineTraceForPathCubie(const FVector StartLocation, const FVector EndLocation, const bool Debug);

	UFUNCTION(BlueprintCallable)
	void BoxTraceForPathCubie(const FVector StartLocation, const FVector EndLocation, const bool Debug);

	UFUNCTION(BlueprintCallable)
	void DeleteComponents(TArray<UActorComponent*> ActorComponent);

	UFUNCTION(BlueprintCallable)
    void DeleteChildActorComponents(TArray<UChildActorComponent *> ChildActorComponents);
};
