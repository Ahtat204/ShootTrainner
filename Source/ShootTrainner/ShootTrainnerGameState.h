// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ShootTrainerPlayerState.h"
#include "GameFramework/GameStateBase.h"
#include "ShootTrainnerGameState.generated.h"


struct FChallenge;

UCLASS()
class SHOOTTRAINNER_API AShootTrainnerGameState : public AGameStateBase
{
	GENERATED_BODY()
	explicit AShootTrainnerGameState(const FObjectInitializer& ObjectInitializer);

public:
	TArray<FChallenge> Challenges;
};

/**
* enum representing the GameState , for example if you're shooting in the training yard gameState will set to challenge
*/
UENUM(Blueprintable)
enum class EPlayerState : uint8
{
	/**
	 * this is the default game state, when the player is not playing any shooting challenge
	 */
	FreeRoam UMETA(DisplayName = "FreeRoam"),
	/**
	 * this is the GameState when the player is playing a shooting challenge
	 */
	Challenge UMETA(DisplayName = "Challenge"),
};

/**
 * an enum representing the difficulty of the challenge from @code Easy @endcode to @code Impossible @endcode 
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

USTRUCT(BlueprintType)
struct FChallenge
{
	GENERATED_BODY()

public:
	/**
	*    Default constructor (needed for UE reflection/Blueprints) FChallenge()
	 */
	FChallenge(): Difficulty(EDifficultyLevel::Easy), Name(TEXT("Default Challenge")), TimeLimit(60.f), ScoreMultiplier(1.f)
	{
	}

	explicit FChallenge(const EDifficultyLevel CDifficulty, const FString& CName, const float CTimeLimit,
	                    const float CScoreMultiplier): Difficulty(CDifficulty), Name(CName), TimeLimit(CTimeLimit),
	                                                   ScoreMultiplier(CScoreMultiplier)
	{
	};
	/**
	 * difficulty of the Challenge
	 */
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Challenge)
	EDifficultyLevel Difficulty;
	/**
	 * Challenge name
	 */
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Challenge)
	FString Name;
	/**
	 * Challenge Time limit
	 */
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Challenge)
	float TimeLimit;
	/**
	 * the rate of which the score increases
	 */
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Challenge)
	float ScoreMultiplier;
	// add accuracy or score decay if the player doesn't hit the target
};
