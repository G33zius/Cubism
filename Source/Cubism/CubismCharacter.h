// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include <Runtime/CinematicCamera/Public/CineCameraComponent.h>
#include <Runtime/CinematicCamera/Public/CineCameraSettings.h>
#include "Logging/LogMacros.h"
#include "CubismCharacter.generated.h"

class UInputComponent;
class USkeletalMeshComponent;
class UCameraComponent;
class UInputAction;
class UInputMappingContext;
struct FInputActionValue;
class ACube;
class ACubie;
class ACubieDoor;
class AShaft;
class ARail;

DECLARE_LOG_CATEGORY_EXTERN(LogTemplateCharacter, Log, All);

UCLASS(config=Game)
class ACubismCharacter : public ACharacter
{
	GENERATED_BODY()

	// /** Pawn mesh: 1st person view (arms; seen only by self) */
	// UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Mesh, meta = (AllowPrivateAccess = "true"))
	// USkeletalMeshComponent* Mesh1P;

	// /** First person camera */
	// UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	// UCameraComponent* FirstPersonCameraComponent;

	// /** MappingContext */
	// UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	// UInputMappingContext* DefaultMappingContext;

	// /** Jump Input Action */
	// UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	// UInputAction* JumpAction;

	// /** Move Input Action */
	// UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	// UInputAction* MoveAction;

	// /** Look Input Action */
	// UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	// class UInputAction* LookAction;
	
public:
	ACubismCharacter();
	// /** Returns Mesh1P subobject **/
	// USkeletalMeshComponent* GetMesh1P() const { return Mesh1P; }
	// /** Returns FirstPersonCameraComponent subobject **/
	// UCameraComponent* GetFirstPersonCameraComponent() const { return FirstPersonCameraComponent; }

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="zCubieReferences")
    ACubie* CurrentCubie;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="zCubieReferences")
    ACubie* PreviousCubie;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="zCubieReferences")
    ACube* Cube;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="zRailReferences")
    ARail* AttachedRail;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="zRailReferences")
    ARail* CanAttachRail;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="zRailReferences")
    ARail* PreviousRail;

	UFUNCTION(BlueprintCallable)
	void UpdateToxicity(float Change);

	UFUNCTION(BlueprintCallable)
	void UpdateHealth(float Change);

	UFUNCTION(BlueprintCallable)
	void UpdateOxygen(float Change);

	UFUNCTION(BlueprintCallable)
	void ConsumeRoomOxygen();
	
	UFUNCTION(BlueprintCallable)
	void ApplyHypoxiaToxicity();

	UFUNCTION(BlueprintCallable)
	void ApplySaturationToxicity();

	UFUNCTION(BlueprintCallable)
	void TakeToxicityDamage();
	
	UFUNCTION(BlueprintCallable)
	void Tax();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "zComponents")
	UCineCameraComponent* CinematicCamera;

	UFUNCTION(BlueprintCallable)
	void AddRailAcceleration(float _MoveActionValueY, ARail* _AttachedRail, UCineCameraComponent* _CinematicCamera);

protected:
	// /** Called for movement input */
	// void Move(const FInputActionValue& Value);

	// /** Called for looking input */
	// void Look(const FInputActionValue& Value);

	// // APawn interface
	// virtual void NotifyControllerChanged() override;
	// virtual void SetupPlayerInputComponent(UInputComponent* InputComponent) override;
	// // End of APawn interface

private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "zDebug", meta = (AllowPrivateAccess = "true"))
	bool bDebugCameraActive = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "zDebug", meta = (AllowPrivateAccess = "true"))
	int64 Int64Max = 9223372036854775807;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "zPlayerData", meta = (AllowPrivateAccess = "true"))
	float MoveActionValueY = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "zPlayerData", meta = (AllowPrivateAccess = "true"))
	float HardLandingMin = 1500.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "zPlayerData", meta = (AllowPrivateAccess = "true"))
	float HardLandingMax = 5000.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "zPlayerData", meta = (AllowPrivateAccess = "true"))
	float MaxRunSpeed = 1200.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "zPlayerData", meta = (AllowPrivateAccess = "true"))
	float MaxWalkSpeed = 300.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "zPlayerData", meta = (AllowPrivateAccess = "true"))
	float MaxRailSpeed = 1000.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "zPlayerData", meta = (AllowPrivateAccess = "true"))
	float MinRailSpeed = -1000.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "zPlayerData", meta = (AllowPrivateAccess = "true"))
	float RailSpeed = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "zPlayerData", meta = (AllowPrivateAccess = "true"))
	float RailAcceleration = 500.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "zPlayerData", meta = (AllowPrivateAccess = "true"))
	float RailFriction = 0.95f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "zPlayerData", meta = (AllowPrivateAccess = "true"))
	float Health = 1.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "zPlayerData", meta = (AllowPrivateAccess = "true"))
	float Toxicity = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "zPlayerData", meta = (AllowPrivateAccess = "true"))
	float ToxicityBaseDamage = 0.01f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "zPlayerData", meta = (AllowPrivateAccess = "true"))
	float RoomOxygenUseRate = 0.01f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "zPlayerData", meta = (AllowPrivateAccess = "true"))
	float HypoxiaToxicityRate = 0.01f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "zPlayerData", meta = (AllowPrivateAccess = "true"))
	float SaturationToxicityRate = 0.01f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "zPlayerData", meta = (AllowPrivateAccess = "true"))
	int64 Coins = 1000000;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "zPlayerData", meta = (AllowPrivateAccess = "true"))
	int Keys = 1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "zPlayerData", meta = (AllowPrivateAccess = "true"))
	int TaxRate = 1000;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "zPlayerData", meta = (AllowPrivateAccess = "true"))
	FVector RailVelocity = FVector(0.0f, 0.0f, 0.0f);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "zPlayerData", meta = (AllowPrivateAccess = "true"))
	FVector PlayerLocationSignXY = FVector(0.0f, 0.0f, 0.0f);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "zPlayerData", meta = (AllowPrivateAccess = "true"))
	ACubieDoor* PlayerDoor;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "zPlayerData", meta = (AllowPrivateAccess = "true"))
	ACubieDoor* Door1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "zPlayerData", meta = (AllowPrivateAccess = "true"))
	ACubieDoor* Door2;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "zPlayerData", meta = (AllowPrivateAccess = "true"))
	AShaft* CurrentShaft;

};

