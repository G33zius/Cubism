// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Cubie.h"
#include "Algo/RandomShuffle.h"
#include "Materials/MaterialInstanceDynamic.h"
#include "Cube.generated.h"

UCLASS()
class CUBISM_API ACube : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACube();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "zCubieData", meta = (AllowPrivateAccess = "true"))
	float CubieSize = 3000.0f;

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "zCubeData", meta = (AllowPrivateAccess = "true"))
	TArray<FVector> Coordinates;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "zCubeData", meta = (AllowPrivateAccess = "true"))
	int CubieCount;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "zCubeData", meta = (AllowPrivateAccess = "true"))
	FVector Dimensions = FVector(3.0f, 3.0f, 3.0f);

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "zMovement", meta = (AllowPrivateAccess = "true"))
	int MovedCount = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "zMovement", meta = (AllowPrivateAccess = "true"))
	float NextMoveTime = 1.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "zCubeData", meta = (AllowPrivateAccess = "true"))
	bool CenterCubieSwitchPressed = false;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "zCubeData", meta = (AllowPrivateAccess = "true"))
	FVector NullCoordinates;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "zCubeData", meta = (AllowPrivateAccess = "true"))
	FVector PlayerStartLocation;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "zCubeData", meta = (AllowPrivateAccess = "true"))
	TArray<AActor*> NullAdjacentCubies;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "zCubeData", meta = (AllowPrivateAccess = "true"))
	int CubieMovedResetCount;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "zCubeData", meta = (AllowPrivateAccess = "true"))
	float MaxDistanceToDestination;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "zCubieData", meta = (AllowPrivateAccess = "true"))
	float NonPrimaryCubieEmissive = .05f;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "zCubieData", meta = (AllowPrivateAccess = "true"))
	float PrimaryCubieEmissive = 1.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "zCubieData", meta = (AllowPrivateAccess = "true"))
	float LastCubieEmissive = 0.0f;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "zCubeData", meta = (AllowPrivateAccess = "true"))
	int CurrentSpawnIndex = 0;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "zCubeData", meta = (AllowPrivateAccess = "true"))
	int CurrentRowsCount = 0;

	UPROPERTY(EditAnywhere, Category = "zCollision")
	TEnumAsByte<ECollisionChannel> TraceChannelProperty = ECC_GameTraceChannel1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "zDebug", meta = (AllowPrivateAccess = "true"))
	float DebugBoxDuration = 1.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "zDebug", meta = (AllowPrivateAccess = "true"))
	FLinearColor Red = FLinearColor(1.0f, 0.0f, 0.0f, 1.0f);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "zDebug", meta = (AllowPrivateAccess = "true"))
	FLinearColor Green = FLinearColor(0.031848f, 1.0f, 0.0f, 1.0f);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "zDebug", meta = (AllowPrivateAccess = "true"))
	FLinearColor Yellow = FLinearColor(1.0f, 0.999622f, 0.0f, 1.0f);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "zDebug", meta = (AllowPrivateAccess = "true"))
	FLinearColor Purple = FLinearColor(0.240724f, 0.0f, 1.0f, 1.0f);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "zDebug", meta = (AllowPrivateAccess = "true"))
	FLinearColor White = FLinearColor(1.0f, 1.0f, 1.0f, 1.0f);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "zDebug", meta = (AllowPrivateAccess = "true"))
	FLinearColor Teal = FLinearColor(0.0f, 1.0f, 0.666614f, 1.0f);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "zDebug", meta = (AllowPrivateAccess = "true"))
	FLinearColor Orange = FLinearColor(0.636458f, 0.124715f, 0.000456f, 1.0f);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "zDebug", meta = (AllowPrivateAccess = "true"))
	FLinearColor LastColor = FLinearColor();

	// Functions

	UFUNCTION(BlueprintCallable)
	void GetAdjacentCoordinates(FVector _Coordinates, TArray<FVector>& AdjacentCoordinates);

	UFUNCTION(BlueprintCallable) 
	void GetIndicesSetCubieCount(int& IndexX, int& IndexY, int& IndexZ);

	UFUNCTION(BlueprintCallable)
	void GetLocationFromCoordinates(FVector _Coordinates, FVector& Location);

	UFUNCTION(BlueprintCallable)
	ACubie* FindNextShiftCubie(TArray<FVector> AdjacentCoordinates, const FVector NullLocation, const bool Debug);

	UFUNCTION(BlueprintCallable)
	void LineTraceForShiftCubie(const FVector StartLocation, const FVector EndLocation, const bool Debug);

	UFUNCTION(BlueprintCallable)
	AActor* LineTraceForCubieGeneric(const FVector StartLocation, const FVector EndLocation, const bool Debug);
	
};

