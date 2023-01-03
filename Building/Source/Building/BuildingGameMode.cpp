// Copyright Epic Games, Inc. All Rights Reserved.

#include "BuildingGameMode.h"
#include "BuildingCharacter.h"
#include "UObject/ConstructorHelpers.h"

ABuildingGameMode::ABuildingGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPersonCPP/Blueprints/ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
