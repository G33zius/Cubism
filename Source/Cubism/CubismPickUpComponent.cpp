// Copyright Epic Games, Inc. All Rights Reserved.

#include "CubismPickUpComponent.h"

UCubismPickUpComponent::UCubismPickUpComponent()
{
	// Setup the Sphere Collision
	SphereRadius = 32.f;
}

void UCubismPickUpComponent::BeginPlay()
{
	Super::BeginPlay();

	// Register our Overlap Event
	OnComponentBeginOverlap.AddDynamic(this, &UCubismPickUpComponent::OnSphereBeginOverlap);
}

void UCubismPickUpComponent::OnSphereBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	// Checking if it is a First Person Character overlapping
	ACubismCharacter* Character = Cast<ACubismCharacter>(OtherActor);
	if(Character != nullptr)
	{
		// Notify that the actor is being picked up
		OnPickUp.Broadcast(Character);

		// Unregister from the Overlap Event so it is no longer triggered
		OnComponentBeginOverlap.RemoveAll(this);
	}
}
