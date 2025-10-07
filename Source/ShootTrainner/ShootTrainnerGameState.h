// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ShootTrainerPlayerState.h"
#include "GameFramework/GameStateBase.h"
#include "ShootTrainnerGameState.generated.h"

/**
 * Forward declaration of the challenge struct.
 * Used to avoid circular dependencies.
 */
struct FChallenge;

/**
 * @class AShootTrainnerGameState
 * @brief Custom GameState class for ShootTrainer.
 *
 * The GameState holds information shared between all players and the server, 
 * such as the available challenges in the training session.
 */
UCLASS()
class SHOOTTRAINNER_API AShootTrainnerGameState : public AGameStateBase
{
	GENERATED_BODY()

public:
	/** Constructor with UE object initializer. */
	explicit AShootTrainnerGameState(const FObjectInitializer& ObjectInitializer);

	/** List of all available challenges in the game session. */
	TArray<FChallenge> Challenges;
};

/**
 * @enum EPlayerState
 * @brief Enum representing the player's current state.
 *
 * Example usage:
 * - @c FreeRoam: The player is free to move around and is not in a challenge.
 * - @c Challenge: The player is currently engaged in a shooting challenge.
 */
UENUM(Blueprintable)
enum class EPlayerState : uint8
{
	/** Default state, when the player is exploring freely. */
	FreeRoam UMETA(DisplayName = "Free Roam"),

	/** State when the player is actively participating in a shooting challenge. */
	Challenge UMETA(DisplayName = "Challenge"),
	
};

/**
 * @enum EDifficultyLevel
 * @brief Enum representing the difficulty level of a challenge.
 *
 * Ranges from @c VeryEasy to @c Insane.
 */
UENUM(Blueprintable)
enum class EDifficultyLevel : uint8
{
	VeryEasy UMETA(DisplayName = "Very Easy"),
	Easy UMETA(DisplayName = "Easy"),
	Normal UMETA(DisplayName = "Normal"),
	Hard UMETA(DisplayName = "Hard"),
	VeryHard UMETA(DisplayName = "Very Hard"),
	Insane UMETA(DisplayName = "Insane"),
};

/**
 * @struct FChallenge
 * @brief Data structure representing a shooting challenge.
 *
 * Contains details such as difficulty, name, time constraints, 
 * and score scaling for the challenge.
 */
USTRUCT(BlueprintType)
struct FChallenge
{
	GENERATED_BODY()

public:
	/** Default constructor (required for UE reflection/Blueprints). */
	FChallenge()
		: Difficulty(EDifficultyLevel::Easy)
		, Name(TEXT("Default Challenge"))
		, TimeLimit(60.f)
		, ScoreMultiplier(1.f)
	{
	}

	/** Parameterized constructor for creating a custom challenge. */
	explicit FChallenge(
		const EDifficultyLevel CDifficulty,
		const FString& CName,
		const float CTimeLimit,
		const float CScoreMultiplier)
		: Difficulty(CDifficulty)
		, Name(CName)
		, TimeLimit(CTimeLimit)
		, ScoreMultiplier(CScoreMultiplier)
	{
	}

	/** Difficulty level of the challenge. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Challenge")
	EDifficultyLevel Difficulty;

	/** Display name of the challenge. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Challenge")
	FString Name;

	/** Time limit (in seconds) to complete the challenge. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Challenge")
	float TimeLimit;

	/** Score multiplier applied during the challenge. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Challenge")
	float ScoreMultiplier;

	// TODO: Add future properties like accuracy tracking or score decay over time.
};
