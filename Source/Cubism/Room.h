// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Room.generated.h"

class ACubie;
class ATrap;

UCLASS()
class CUBISM_API ARoom : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ARoom();
	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "zCubieData")
	ACubie* ParentCubie;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="zRoomData")
	FRandomStream RoomStream;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="zRoomData")
	int RoomStreamSeed;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "zComponents")
	USceneComponent* Root;

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="zRoomData", meta = (AllowPrivateAccess = "true"))
	int32 Int32Max = 2147483647;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="zRoomData", meta = (AllowPrivateAccess = "true"))
    TArray<UStaticMesh*> Shapes;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="zTrapData", meta = (AllowPrivateAccess = "true"))
	ATrap* Trap;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="zRoomData", meta = (AllowPrivateAccess = "true"))
	int32 ShapePick = 0;
};
