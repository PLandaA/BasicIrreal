// Copyright Epic Games, Inc. All Rights Reserved.

#include "BasicIrrealGameMode.h"
#include "BasicIrrealCharacter.h"
#include "UObject/ConstructorHelpers.h"

ABasicIrrealGameMode::ABasicIrrealGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPerson/Blueprints/BP_FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

}
