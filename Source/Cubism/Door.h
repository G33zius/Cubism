// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Door.generated.h"

UCLASS()
class CUBISM_API ADoor : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ADoor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "zDoorData", meta = (AllowPrivateAccess = "true"))
	FVector StartLocation = FVector();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "zDoorData", meta = (AllowPrivateAccess = "true"))
	FVector EndLocation = FVector();
};
