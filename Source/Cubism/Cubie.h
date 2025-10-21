// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Algo/RandomShuffle.h"
#include "Cubie.generated.h"

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

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "zCubieData", meta = (AllowPrivateAccess = "true"))
	FVector Coordinates = FVector();

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "zCubieData", meta = (AllowPrivateAccess = "true"))
	bool HasMoved = false;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "zCubieData", meta = (AllowPrivateAccess = "true"))
	bool IsCenterCubie = false;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "zCubieData", meta = (AllowPrivateAccess = "true"))
	bool IsExitCubie = false;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "zCubieData", meta = (AllowPrivateAccess = "true"))
	bool IsEntranceCubie = false;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "zCubieData", meta = (AllowPrivateAccess = "true"))
	bool IsActivePathCubie = false;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "zCubieData", meta = (AllowPrivateAccess = "true"))
	bool IsPlayerCubie = false;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "zCubieData", meta = (AllowPrivateAccess = "true"))
	bool HasSafePath = false;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "zCubieData", meta = (AllowPrivateAccess = "true"))
	bool IsBestPathSelected = false;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "zCubieData", meta = (AllowPrivateAccess = "true"))
	bool IsAwaitingVisit = false;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "zCubieData", meta = (AllowPrivateAccess = "true"))
	bool WasVisited = false;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "zCubieData", meta = (AllowPrivateAccess = "true"))
	bool UseCubeColoring = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "zCubieData", meta = (AllowPrivateAccess = "true"))
	bool IsTestCubie = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "zCubieData", meta = (AllowPrivateAccess = "true"))
	int Seed = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "zCubieData", meta = (AllowPrivateAccess = "true"))
	FLinearColor RectLightColor = FColor::FromHex("008EFFFF");

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "zCubieData", meta = (AllowPrivateAccess = "true"))
	FLinearColor LastColor = FColor::White;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "zCubieData", meta = (AllowPrivateAccess = "true"))
	float RectLightIntensity = 1000000.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "zCubieData", meta = (AllowPrivateAccess = "true"))
	float RectLightAttenuationRad = 2150.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "zCubieData", meta = (AllowPrivateAccess = "true"))
	float LastCubieEmissive = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "zCubieData", meta = (AllowPrivateAccess = "true"))
	float RectLightBarnDoorLength = 3000.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "zCubieData", meta = (AllowPrivateAccess = "true"))
	int CubieStreamSeed = 0;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "zCubieData", meta = (AllowPrivateAccess = "true"))
	int Int32Max = 2147483647;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "zCubieData", meta = (AllowPrivateAccess = "true"))
	FVector PlayerStartLocation = FVector();

private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "zCubieData", meta = (AllowPrivateAccess = "true"))
	float CubieSize = 3000.0f;

	// TODO: ParentCube

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

	UPROPERTY(EditDefaultsOnly, Category = "zCollision")
	TEnumAsByte<ECollisionChannel> TraceChannelProperty = ECC_GameTraceChannel1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "zDebug", meta = (AllowPrivateAccess = "true"))
	float DebugBoxDuration = 0.5f;

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
