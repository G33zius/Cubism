// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/BoxComponent.h"
#include "CubieDoor.generated.h"

UCLASS()
class CUBISM_API ACubieDoor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACubieDoor();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "zComponents")
    UStaticMeshComponent* DoorMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "zComponents")
    UBoxComponent* DoorCollisionBox;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "zComponents")
	USceneComponent* Root;

private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "zDoorData", meta = (AllowPrivateAccess = "true"))
	FVector StartLocation = FVector();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "zDoorData", meta = (AllowPrivateAccess = "true"))
	FVector EndLocation = FVector();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "zDoorData", meta = (AllowPrivateAccess = "true"))
	bool bIsDoorMoving = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "zDoorData", meta = (AllowPrivateAccess = "true"))
	bool bIsDoorOpen = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "zDoorData", meta = (AllowPrivateAccess = "true"))
	bool OverlapOutside = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "zDoorData", meta = (AllowPrivateAccess = "true"))
	bool OverlapInside = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "zDoorData", meta = (AllowPrivateAccess = "true"))
	bool IsDoorBlocked = false;

};
