// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/BoxComponent.h"
#include "Components/RectLightComponent.h"
#include "Rail.generated.h"

UCLASS()
class CUBISM_API ARail : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ARail();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "zComponents")
	USceneComponent* Root;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "zComponents")
    UStaticMeshComponent* RailMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "zComponents")
    UBoxComponent* RailCollisionBox;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "zComponents")
	URectLightComponent* RectLight;

private:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "zRailData", meta = (AllowPrivateAccess = "true"))
	float RailThickness = 10.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "zRailData", meta = (AllowPrivateAccess = "true"))
	float RailLength = 1200.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "zRailData", meta = (AllowPrivateAccess = "true"))
	float RailWidth = 20.0f;

};
