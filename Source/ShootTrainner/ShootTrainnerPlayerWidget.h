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

private:
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(ToolTip="", AllowPrivateAccess=true))
	FChallenge Challenge;
	/* text block displaying the name of the challenge  */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(ToolTip="text block displaying the name of the challenge ",BindWidget, AllowPrivateAccess=true))
	UTextBlock* ChallengeName;
	/* text block displaying the duration of the challenge */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(ToolTip=" text block displaying the duration of the challenge",BindWidget, AllowPrivateAccess=true))
	UTextBlock* Time;
	/*text block displaying the score multiplier of the challenge*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(BindWidget, AllowPrivateAccess=true))
	UTextBlock* ScoreMultiplier;
	/* text block displaying the difficulty level of the challenge*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(BindWidget, AllowPrivateAccess=true))
	UTextBlock* Difficulty;

	public:
	void SetChallengeName(UTextBlock* const ChallengeName);
	void SetTime(UTextBlock* const Time);
	void SetScoreMultiplier(UTextBlock* const ScoreMultiplier);
	void SetDifficulty(UTextBlock* const Difficulty);
	UFUNCTION(BlueprintCallable)
	void Setup(const FChallenge& chall);
	
};


