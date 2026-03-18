// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/RectLightComponent.h"
#include "Algo/RandomShuffle.h"
#include "Kismet/GameplayStatics.h"
#include "Cubie.generated.h"


class ACube;
class ACubieDoor;
class AShaft;
class ARail;
class ARoom;

UCLASS()
class CUBISM_API ACubie : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACubie();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "zCubieData")
	FVector Coordinates = FVector();

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "zCubieData")
	bool bHasMoved = false;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "zCubieData")
	bool bIsCenterCubie = false;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "zCubieData")
	bool bIsExitCubie = false;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "zCubieData")
	bool bIsEntranceCubie = false;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "zCubieData")
	bool bIsActivePathCubie = false;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "zCubieData")
	bool bIsPlayerCubie = false;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "zCubieData")
	bool bHasSafePath = false;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "zCubieData")
	bool bIsBestPathSelected = false;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "zCubieData")
	bool bIsAwaitingVisit = false;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "zCubieData")
	bool bWasVisited = false;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "zCubieData")
	bool bUseCubeColoring = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "zCubieData")
	bool bIsTestCubie = false;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "zCubieData")
	bool bIsEdgeCubie = false;

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
	APlayerController* PlayerController;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "zCubieData")
	float CubieSize = 3000.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "zCubieData")
	FVector LastCoordinates = FVector();

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "zCubieData")
	FVector RailScale = FVector(1.0f, 1.0f, 1205.0f);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "zComponents")
	UStaticMesh* CubiePanelMesh;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "zCubieData")
	float CubiePanelLocationOffset = 1200.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "zCubieData", meta = (AllowPrivateAccess = "true"))
	bool bIsPathCubie = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "zCubieData")
	TArray<FTransform> CubiePanelTransforms = TArray<FTransform>(
	{
		FTransform(FRotator(0.0f, 0.0f, 0.0f), FVector(-CubiePanelLocationOffset, 0.0f, 0.0f), FVector(1.0f, 1.0f, 1.0f)),
		FTransform(FRotator(0.0f, 180.0f, 0.0f), FVector(CubiePanelLocationOffset, 0.0f, 0.0f), FVector(1.0f, 1.0f, 1.0f)),
		FTransform(FRotator(0.0f, 90.0f, 0.0f), FVector(0.0f, -CubiePanelLocationOffset, 0.0f), FVector(1.0f, 1.0f, 1.0f)),
		FTransform(FRotator(0.0f, -90.0f, 0.0f), FVector(0.0f, CubiePanelLocationOffset, 0.0f), FVector(1.0f, 1.0f, 1.0f)),
		FTransform(FRotator(90.0f, 0.0f, 0.0f), FVector(0.0f, 0.0f, -CubiePanelLocationOffset), FVector(1.0f, 1.0f, 1.0f)),
		FTransform(FRotator(-90.0f, 0.0f, 0.0f), FVector(0.0f, 0.0f, CubiePanelLocationOffset), FVector(1.0f, 1.0f, 1.0f))
	});

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "zCubieData")
	float KineticCubeWallLocationOffset = 150.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "zCubieData")
	TArray<FVector> KineticCubeWallLocations = TArray<FVector>(
	{
		FVector(KineticCubeWallLocationOffset, 0.0f, 0.0f),
		FVector(CubieSize - KineticCubeWallLocationOffset, 0.0f, 0.0f),
		FVector(0.0f, KineticCubeWallLocationOffset, 0.0f),
		FVector(0.0f, CubieSize - KineticCubeWallLocationOffset, 0.0f),
		FVector(0.0f, 0.0f, KineticCubeWallLocationOffset),
		FVector(0.0f, 0.0f, CubieSize - KineticCubeWallLocationOffset)
	});

	UFUNCTION(BlueprintCallable)
	void UpdateOxygen(float Change);
	
	UFUNCTION(BlueprintCallable)
	void SpawnKineticCubes(bool bDoSpawn = true);

	UFUNCTION(BlueprintCallable)
	void SpawnCubiePanels(bool bDoSpawn = true);

	UFUNCTION(BlueprintCallable)
	void SpawnKineticCubeWalls(bool bDoSpawn = true);

	UFUNCTION(BlueprintCallable)
	void CacheCubieVisuals();

	UFUNCTION(BlueprintCallable)
	void RestoreCubieVisuals();

	UFUNCTION(BlueprintCallable)
	void PressCenterCubieSwitch();

	UFUNCTION(BlueprintCallable)
	void GetRandomCubiePickChance(bool bDebug = false, float DebugDuration = 3.0f);

	UFUNCTION(BlueprintCallable)
	bool DeriveCanDespawn(bool bDebug= false, float DebugDuration = 3.0f);

	UFUNCTION(BlueprintCallable)
	void DestroyActorComponentsByArray(TArray<UActorComponent*> ActorComponent);

	UFUNCTION(BlueprintCallable)
    void DestroyChildActorComponentsByArray(TArray<UChildActorComponent *> ChildActorComponents);

	UFUNCTION(BlueprintCallable)
	void DestroyActorsByArray(TArray<AActor*> Actors);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "zComponents")
	USceneComponent* Root;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "zComponents")
    UStaticMeshComponent* DebugCubieMeshComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "zComponents")
	TArray<URectLightComponent*> RectLights;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "zComponents")
    TArray<UStaticMeshComponent*> CubiePanelMeshComponents;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "zComponents")
	TArray<ACubieDoor*> Doors;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "zComponents")
	TArray<ARail*> Rails;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "zComponents")
	TArray<AShaft*> Shafts;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "zComponents")
	ARoom* Room;

private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "zCubieData", meta = (AllowPrivateAccess = "true"))
	float RandomChanceOfCubiePick;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "zCubieData", meta = (AllowPrivateAccess = "true"))
	float DistanceToDestination;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "zCubieData", meta = (AllowPrivateAccess = "true"))
	float Damage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "zCubieData", meta = (AllowPrivateAccess = "true"))
	float KineticFallbackMeshLocationOffset = 1251.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "zCubieData", meta = (AllowPrivateAccess = "true"))
	TArray<AActor*> PathAdjacentCubies;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "zCubieData", meta = (AllowPrivateAccess = "true"))
	TArray<AActor*> AdjacentCubies;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "zCubieData", meta = (AllowPrivateAccess = "true"))
	TArray<UStaticMeshComponent*> KineticCubeFallbackMeshes;

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
	bool bIsLoaded = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "zCubieData", meta = (AllowPrivateAccess = "true"))
	bool bCanDespawn = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "zCubieData", meta = (AllowPrivateAccess = "true"))
	bool bPanelsLoaded = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "zCubieData", meta = (AllowPrivateAccess = "true"))
	bool bKineticCubesLoaded = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "zCubieData", meta = (AllowPrivateAccess = "true"))
	bool bRailsLoaded = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "zCubieData", meta = (AllowPrivateAccess = "true"))
	bool bDoorsLoaded = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "zCubieData", meta = (AllowPrivateAccess = "true"))
	bool bRoomLoaded = false;
	
	UFUNCTION(BlueprintCallable)
	void GetLocationFromCoordinates(FVector _Coordinates, FVector& Location);

	UFUNCTION(BlueprintCallable)
	void LerpToLocation(const FVector NewLocation, const float Alpha);

	UFUNCTION(BlueprintCallable)
	void UpdateCoordinatesFromShift(FVector _LastCoordinates, FVector LastNullCoordinates, FVector& NewCoordinates, FVector& NewNullCoordinates);

	UFUNCTION(BlueprintCallable)
	void GetAdjacentCoordinates(FVector _Coordinates, TArray<FVector>& AdjacentCoordinates);

	UFUNCTION(BlueprintCallable)
	ACubie* FindNextPathCubie(const bool bDebug = false);

	UFUNCTION(BlueprintCallable)
    TArray<AActor*> GetAdjacentCubies(const bool bDebug = false);

	UFUNCTION(BlueprintCallable)
    void LineTraceForAdjacentCubie(const FVector StartLocation, const FVector EndLocation, const bool bDebug = false);

    UFUNCTION(BlueprintCallable)
	ACubie* BoxFindNextPathToCubie(FVector const EndCoordinates, const bool bDebug = false);

	UFUNCTION(BlueprintCallable)
	void LineTraceForPathCubie(const FVector StartLocation, const FVector EndLocation, const bool bDebug = false);

	UFUNCTION(BlueprintCallable)
	void BoxTraceForPathCubie(const FVector StartLocation, const FVector EndLocation, const bool bDebug = false);
	
	UFUNCTION(BlueprintCallable)
	void GetPlayer(ACubismCharacter*& Player);
};
