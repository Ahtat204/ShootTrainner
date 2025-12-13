// Copyright Epic Games, Inc. All Rights Reserved.

#include "ShootTrainnerGameMode.h"
#include "ShootTrainnerGameState.h"
#include "ShootTrainnerPlayerController.h"

#include "UObject/ConstructorHelpers.h"

AShootTrainnerGameMode::AShootTrainnerGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(
		TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	
	static ConstructorHelpers::FClassFinder<APlayerController> PlayeControllerBPClass(
		TEXT("/Game/BP_PlayerController"));
	if (PlayerPawnBPClass.Class != nullptr)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
	GameStateClass = AShootTrainnerGameState::StaticClass();
	PlayerStateClass = AShootTrainerPlayerState::StaticClass();
	//	HUDClass=AShootTrainnerHUD::StaticClass();
	//if (PlayeControllerBPClass.Class != nullptr)PlayerControllerClass = PlayeControllerBPClass.Class;
	PlayerControllerClass=AShootTrainnerPlayerController::StaticClass();
}

void AShootTrainnerGameMode::BeginPlay()
{
	Super::BeginPlay();
}
