// Copyright Epic Games, Inc. All Rights Reserved.

#include "ShootTrainnerGameMode.h"
#include "ShootTrainnerCharacter.h"
#include "UObject/ConstructorHelpers.h"

AShootTrainnerGameMode::AShootTrainnerGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
