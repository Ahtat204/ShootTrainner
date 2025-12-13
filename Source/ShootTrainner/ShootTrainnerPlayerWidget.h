// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ShootTrainnerGameState.h"
#include "Blueprint/UserWidget.h"
#include "ShootTrainnerPlayerWidget.generated.h"

class AShootTrainnerCharacter;
struct FChallenge;
class UTextBlock;
/**
 * 
 */


UCLASS()
class SHOOTTRAINNER_API UShootTrainnerPlayerWidget : public UUserWidget
{
protected:
	virtual void NativeConstruct() override;

	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

private:
	GENERATED_BODY()

public:
#pragma region fields
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(ToolTip="", AllowPrivateAccess=true))
	FChallenge Challenge;
	/* text block displaying the name of the challenge  */
	UPROPERTY(EditAnywhere, BlueprintReadWrite,
		meta=(ToolTip="text block displaying the name of the challenge ", BindWidget, AllowPrivateAccess=true))
	UTextBlock* ChallengeName;
	/* text block displaying the duration of the challenge */
	UPROPERTY(EditAnywhere, BlueprintReadWrite,
		meta=(ToolTip=" text block displaying the duration of the challenge", BindWidget, AllowPrivateAccess=true))
	UTextBlock* Time;
	/*text block displaying the score multiplier of the challenge*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(BindWidget, AllowPrivateAccess=true))
	UTextBlock* ScoreMultiplier;
	/* text block displaying the difficulty level of the challenge*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(BindWidget, AllowPrivateAccess=true))
	UTextBlock* Difficulty;

	int32 elapsedTime=1;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(ToolTip="", AllowPrivateAccess=true))
	FTimerHandle ChallengeTimer;
#pragma endregion
#pragma region functions
	void SetChallengeName(UTextBlock* const ChallengeName);
	void SetTime();
	void SetScoreMultiplier(UTextBlock* const ScoreMultiplier);
	void SetDifficulty(UTextBlock* const Difficulty);
	void UpdateTime();
#pragma endregion
};
