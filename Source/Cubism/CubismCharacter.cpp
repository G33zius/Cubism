// Copyright Epic Games, Inc. All Rights Reserved.

#include "CubismCharacter.h"
#include "CubismProjectile.h"
#include "Animation/AnimInstance.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"
#include "Engine/LocalPlayer.h"
#include "Cubie.h"
#include "Rail.h"


DEFINE_LOG_CATEGORY(LogTemplateCharacter);

//////////////////////////////////////////////////////////////////////////
// ACubismCharacter

ACubismCharacter::ACubismCharacter()
{
	// // Create a CameraComponent	
	// FirstPersonCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
	// FirstPersonCameraComponent->SetupAttachment(GetCapsuleComponent());
	// FirstPersonCameraComponent->SetRelativeLocation(FVector(-10.f, 0.f, 60.f)); // Position the camera
	// FirstPersonCameraComponent->bUsePawnControlRotation = true;

	// // Create a mesh component that will be used when being viewed from a '1st person' view (when controlling this pawn)
	// Mesh1P = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("CharacterMesh1P"));
	// Mesh1P->SetOnlyOwnerSee(true);
	// Mesh1P->SetupAttachment(FirstPersonCameraComponent);
	// Mesh1P->bCastDynamicShadow = false;
	// Mesh1P->CastShadow = false;
	// Mesh1P->SetRelativeLocation(FVector(-30.f, 0.f, -150.f));

	CinematicCamera = CreateDefaultSubobject<UCineCameraComponent>(TEXT("CinematicCamera"));
	CinematicCamera->SetupAttachment(GetMesh());
	CinematicCamera->PrimaryComponentTick.bCanEverTick = false;
	CinematicCamera->PrimaryComponentTick.bStartWithTickEnabled = false;
	CinematicCamera->SetRelativeLocation(FVector((3.878495f, 17.816848f, 0.0f)));
	CinematicCamera->SetRelativeRotation(FRotator(90.0f, 0.0f, 90.0f));
	// CinematicCamera->Filmback.SetFilmbackPresetByName(TEXT("Super 16mm"));
	// CinematicCamera->LensSettings.SetLensPresetByName(TEXT("12mm"));
	// CinematicCamera->SetAttachSocketName(TEXT("HeadSocket"));
	CinematicCamera->SetCurrentFocalLength(12.0f);
	// CinematicCamera->bConstraintAspectRatio = false;
	CinematicCamera->bUsePawnControlRotation = true;
	
}

void ACubismCharacter::UpdateToxicity(float Change)
{
	Toxicity += Change;
}

void ACubismCharacter::UpdateHealth(float Change)
{
	Health += Change;
}

void ACubismCharacter::UpdateOxygen(float Change)
{
	if (CurrentCubie){
		CurrentCubie->RoomOxygen += Change;
	}
}

void ACubismCharacter::ConsumeRoomOxygen()
{
	if (CurrentCubie){
		float OxygenUse = FMath::Clamp(RoomOxygenUseRate * -1 * GetWorld()->GetDeltaSeconds(), -1.0f, 0.0f);
		CurrentCubie->UpdateOxygen(OxygenUse);
	}
}

void ACubismCharacter::ApplyHypoxiaToxicity()
{
	if (CurrentCubie && CurrentCubie->RoomOxygen <= 0.0f)
	{
		float ToxicityIncrease = FMath::Clamp(HypoxiaToxicityRate * GetWorld()->GetDeltaSeconds(), 0.0f, 1.0f);
		UpdateToxicity(ToxicityIncrease);
	}
}

void ACubismCharacter::ApplySaturationToxicity()
{
	if (CurrentCubie){
		float ToxicityIncrease = FMath::Clamp(SaturationToxicityRate * CurrentCubie->RoomSaturation * GetWorld()->GetDeltaSeconds(), 0.0f, 1.0f);
		UpdateToxicity(ToxicityIncrease);
	}
}

void ACubismCharacter::TakeToxicityDamage()
{
	if (Toxicity > 0.5f)
	{
		float Damage = FMath::Clamp(ToxicityBaseDamage * -1 * (Toxicity + 1) * GetWorld()->GetDeltaSeconds(), -1.0f, 0.0f);
		UpdateHealth(Damage);
	}
}

void ACubismCharacter::Tax()
{
	Coins = FMath::Clamp(Coins - TaxRate * GetWorld()->GetDeltaSeconds(), 0, Int64Max);
}

void ACubismCharacter::AddRailAcceleration(float _MoveActionValueY, ARail *_AttachedRail, UCineCameraComponent* _CinematicCamera)
{
	if (!AttachedRail || !AttachedRail->RailCollisionBox){
		return;
	}
	FVector UpVector = AttachedRail->RailCollisionBox->GetUpVector();
	FVector ForwardVector = _CinematicCamera->GetForwardVector();
	float DotProduct = FVector::DotProduct(UpVector, ForwardVector);
	float RailSpeedUnclamped = RailSpeed + (FMath::Sign(_MoveActionValueY) * RailAcceleration * DotProduct * GetWorld()->GetDeltaSeconds());
	RailSpeed = FMath::Clamp(RailSpeedUnclamped, MinRailSpeed, MaxRailSpeed);
}

//////////////////////////////////////////////////////////////////////////// Input

// void ACubismCharacter::NotifyControllerChanged()
// {
// 	Super::NotifyControllerChanged();

// 	// Add Input Mapping Context
// 	if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
// 	{
// 		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
// 		{
// 			Subsystem->AddMappingContext(DefaultMappingContext, 0);
// 		}
// 	}
// }

// void ACubismCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
// {	
// 	// Set up action bindings
// 	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent))
// 	{
// 		// Jumping
// 		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &ACharacter::Jump);
// 		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);

// 		// Moving
// 		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ACubismCharacter::Move);

// 		// Looking
// 		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &ACubismCharacter::Look);
// 	}
// 	else
// 	{
// 		UE_LOG(LogTemplateCharacter, Error, TEXT("'%s' Failed to find an Enhanced Input Component! This template is built to use the Enhanced Input system. If you intend to use the legacy system, then you will need to update this C++ file."), *GetNameSafe(this));
// 	}
// }


// void ACubismCharacter::Move(const FInputActionValue& Value)
// {
// 	// input is a Vector2D
// 	FVector2D MovementVector = Value.Get<FVector2D>();

// 	if (Controller != nullptr)
// 	{
// 		// add movement 
// 		AddMovementInput(GetActorForwardVector(), MovementVector.Y);
// 		AddMovementInput(GetActorRightVector(), MovementVector.X);
// 	}
// }

// void ACubismCharacter::Look(const FInputActionValue& Value)
// {
// 	// input is a Vector2D
// 	FVector2D LookAxisVector = Value.Get<FVector2D>();

// 	if (Controller != nullptr)
// 	{
// 		// add yaw and pitch input to controller
// 		AddControllerYawInput(LookAxisVector.X);
// 		AddControllerPitchInput(LookAxisVector.Y);
// 	}
// }