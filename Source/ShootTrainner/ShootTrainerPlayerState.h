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
public:
	[[nodiscard]] FORCEINLINE float GetAccuracy() const { return Accuracy; };
	void SetAccuracy(const float Accuracy);
	[[nodiscard]] FORCEINLINE uint8 GetShotsFiredCount() const { return ShotsFiredCount; };
	void SetShotsFiredCount(const uint8 ShotsFiredCount);
	[[nodiscard]] FORCEINLINE uint8 GetTargetHit() const { return TargetHit; };
	void SetTargetHit(const uint8 TargetHit);
	[[nodiscard]] FORCEINLINE float GetTimePlayed() const { return TimePlayed; };
	void SetTimePlayed(const float TimePlayed);

private:
	GENERATED_BODY()

public:
	/** Constructor */
	explicit AShootTrainerPlayerState(const FObjectInitializer& ObjectInitializer);

private:
	/**
	 * The player’s shooting accuracy.
	 * Calculated as Hits / ShotsFired, stored as a float (start with 1 as 100%, decays with miss count miss distance).
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

	/**
	 * 
	 * @param Accuracies the accuracy from each challenge played
	 * @returns the Average Accuracy 
	 */
	void EvaluateAccuracy(TArray<float> Accuracies)
	{
		for (const auto acc : Accuracies)
		{
			Accuracy += acc / Accuracies.Num();
		}
	};

	/**
	 * 
	 * @param distance euclidean distance between center of the target and the hit point(where the bullet hit).
	 * To avoid unpredictable behaviour (like negative accuracy) will count accuracy for bullets that hit target)
	 */
	float SetAccuracyPerCent(float distance) const
	{
		return FMath::Clamp(Accuracy - distance, 0, 1);
	}
};
