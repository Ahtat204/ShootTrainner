// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ShootTrainnerGameState.h"
#include "Blueprint/UserWidget.h"
#include "ShootTrainnerPlayerWidget.generated.h"

class AChallengeGate;
class AShootTrainnerCharacter;
struct FChallenge;
class UTextBlock;
/**
 * 
 */


UCLASS()
class SHOOTTRAINNER_API UShootTrainnerPlayerWidget : public UUserWidget
{
	GENERATED_BODY()

public:
#pragma region fields
	UPROPERTY(EditAnywhere, BlueprintReadWrite,
		meta=(ToolTip="text block the name of the challenge", AllowPrivateAccess=true))
	FChallenge Challenge;
	UPROPERTY(EditAnywhere, BlueprintReadWrite,
	meta=(ToolTip="text block the name of the challenge", AllowPrivateAccess=true))
	AChallengeGate* ChallengeGate;
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
	int32 elapsedTime = 1;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(ToolTip="", AllowPrivateAccess=true))
	FTimerHandle ChallengeTimer;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(BindWidget, AllowPrivateAccess=true))
	UTextBlock* TargetHit;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(BindWidget, AllowPrivateAccess=true))
	UTextBlock* Score;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(BindWidget, AllowPrivateAccess=true))
	UTextBlock* Accuracy;
	
#pragma endregion
#pragma region functions
protected:
	virtual void NativeConstruct() override;
	void SetTime();
	float SetAccuracyPerCent(float distance);
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;
#pragma endregion
};
