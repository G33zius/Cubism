// Copyright Epic Games, Inc. All Rights Reserved.

#include "CubismGameMode.h"
#include "CubismCharacter.h"
#include "UObject/ConstructorHelpers.h"

ACubismGameMode::ACubismGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPerson/Blueprints/BP_FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

}
