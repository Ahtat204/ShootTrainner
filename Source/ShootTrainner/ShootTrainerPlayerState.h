// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "ShootTrainerPlayerState.generated.h"

/**
 * AShootTrainerPlayerState
 * 
 * This class represents the state of a player in the ShootTrainer game.
 * It stores per-player statistics and metrics that persist across rounds or challenges.
 * It extends APlayerState, making it suitable for both single-player and multiplayer scenarios.
 */
UCLASS()
class SHOOTTRAINNER_API AShootTrainerPlayerState : public APlayerState
{
	GENERATED_BODY()

public:
	/** Constructor */
	explicit AShootTrainerPlayerState(const FObjectInitializer& ObjectInitializer);

private:
	
	/**
	 * The player’s shooting accuracy.
	 * Calculated as Hits / ShotsFired, stored as a float (0.0 to 100.0 for percentage representation).
	 */
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Stats, meta = (AllowPrivateAccess = "true"))
	float Accuracy;

	/**
	 * The total number of shots fired by the player in the current challenge.
	 * Helps calculate accuracy and track shooting behavior.
	 */
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Stats, meta = (AllowPrivateAccess = "true"))
	uint8 ShotsFiredCount;

	/**
	 * The total number of targets hit by the player in the current challenge.
	 * Used to track performance and calculate accuracy.
	 */
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Stats, meta = (AllowPrivateAccess = "true"))
	uint8 TargetHit;

	/**
	 * The total time the player has spent in the challenge or game session.
	 * Stored as a float in seconds.
	 */
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Stats, meta = (AllowPrivateAccess = "true"))
	float TimePlayed;
};


