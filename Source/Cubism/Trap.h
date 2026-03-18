// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CubismCharacter.h"
#include "Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Trap.generated.h"

// class UNiagaraComponent;
class ARoom;

UCLASS()
class CUBISM_API ATrap : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATrap();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "zTrapData")
	// FText TrapType;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "zTrapData")
	float ActivationDistance = 3000.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "zTrapData")
	float FireScale = 1.0f;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "zRoomData")
	ARoom* ParentRoom;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "zTrapData")
	float SaturationRate = 0.01f;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "zComponents")
	UBoxComponent* TrapCollisionBox;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "zTrapData")
	float TrapOxygenUse = 0.0f;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "zComponents")
	USceneComponent* Root;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "zComponents")
    UStaticMeshComponent* TrapMesh;

	// UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "zComponents")
	// UNiagaraComponent* TrapEffect;

private:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "zTrapData", meta = (AllowPrivateAccess = "true"))
	float BaseDamage = 10.0f;

	UFUNCTION(BlueprintCallable)
	void GetDistanceToPlayer(float& DistanceToPlayer);

	UFUNCTION(BlueprintCallable)
	void GetPlayer(ACubismCharacter*& Player);

	UFUNCTION(BlueprintCallable)
	void SetCalculatedDamageInverseSquare(float _DistanceToPlayer, float& CalculatedDamage);
};
