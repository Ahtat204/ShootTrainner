// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "ShootTrainnerGameMode.generated.h"


UCLASS(minimalapi)
class AShootTrainnerGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	AShootTrainnerGameMode();

	virtual void BeginPlay() override;
	
};



