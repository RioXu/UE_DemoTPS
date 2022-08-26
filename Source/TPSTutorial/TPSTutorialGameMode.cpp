// Copyright Epic Games, Inc. All Rights Reserved.

#include "TPSTutorialGameMode.h"
#include "TPSTutorialCharacter.h"
#include "UObject/ConstructorHelpers.h"

ATPSTutorialGameMode::ATPSTutorialGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPersonCPP/Blueprints/ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
