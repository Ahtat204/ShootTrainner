// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "ShootTrainerPlayerState.generated.h"


/**
 * @enum EOverlappingState
 * @brief Represents the state of overlap events between Actors.
 *
 * This enum is intended to be used like a simple state machine
 * for handling overlap logic. Instead of relying on multiple 
 * boolean flags, the enum tracks the current overlap state in 
 * a clear and extendable way.
 *
 * Example usage:
 * - @c None    : No overlap is currently occurring.
 * - @c Started : The overlap event has just begun (OnActorBeginOverlap).
 * - @c Ended   : The overlap event has just ended (OnActorEndOverlap).
 */
UENUM(Category=State)
enum class EOverlappingState : uint8
{
	/** No overlap is active. */
	None UMETA(DisplayName = "None"),

	/** Overlap has just started. */
	Started UMETA(DisplayName = "Started"),

	/** Overlap has just ended. */
	Ended UMETA(DisplayName = "Ended"),
};
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


