// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/BoxComponent.h"
#include "Trap.generated.h"

// class UNiagaraComponent;

UCLASS()
class CUBISM_API ATrap : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATrap();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "zTrapData")
	// FText TrapType;

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "zComponents")
	USceneComponent* Root;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "zComponents")
    UStaticMeshComponent* TrapMesh;

	// UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "zComponents")
	// UNiagaraComponent* TrapEffect;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "zComponents")
	UBoxComponent* TrapCollisionBox;


private:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "zTrapData", meta = (AllowPrivateAccess = "true"))
	float BaseDamage = 10.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "zTrapData", meta = (AllowPrivateAccess = "true"))
	float CalculatedDamage = 10.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "zTrapData", meta = (AllowPrivateAccess = "true"))
	FVector DistanceToPlayer = FVector::ZeroVector;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "zTrapData", meta = (AllowPrivateAccess = "true"))
	float ActivationDistance = 3000.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "zTrapData", meta = (AllowPrivateAccess = "true"))
	float SaturationRate = .01f;

};
