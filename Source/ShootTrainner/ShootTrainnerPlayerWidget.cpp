// Fill out your copyright notice in the Description page of Project Settings.


#include "ShootTrainnerPlayerWidget.h"

#include "ChallengeGate.h"
#include"ShootTrainnerGameState.h"
#include "Target.h"
#include "Components/TextBlock.h"

void UShootTrainnerPlayerWidget::NativeConstruct()
{
	Super::NativeConstruct();
	Challenge=ChallengeGate->Challenge;
	GetWorld()->GetTimerManager().SetTimer(ChallengeTimer,this,&UShootTrainnerPlayerWidget::SetTime,1.0f,true);
	if (ChallengeName) ChallengeName->SetText(FText::FromString(Challenge.Name));
	if (ScoreMultiplier)ScoreMultiplier->SetText(FText::AsNumber(Challenge.ScoreMultiplier));
	if (Time)Time->SetText(FText::AsNumber(Challenge.TimeLimit));
	if (Difficulty)Difficulty->SetText(FText::FromString(Challenge.DifficultyName));
	
}
void UShootTrainnerPlayerWidget::SetTime()
{
	if (Time )
	{
		if (Challenge.TimeLimit<0)
		{
			ChallengeTimer.Invalidate();
			return;
		}
		Time->SetText(FText::AsNumber(Challenge.TimeLimit));
		Challenge.TimeLimit--;
	}
}
//this is not an efficient way to do it , as this function gets called frequently, like Unity's Update
void UShootTrainnerPlayerWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);
	if (TargetHit) TargetHit->SetText(FText::AsNumber(ChallengeGate->ChallengeTarget->Hits));
	if (Accuracy) Accuracy->SetText(FText::AsNumber(SetAccuracyPerCent(ChallengeGate->ChallengeTarget->distance)));
}

float UShootTrainnerPlayerWidget::SetAccuracyPerCent(float distance)
 
{
	auto Acc = 100 - FMath::Loge(distance);
	return FMath::Clamp(Acc, 0, 100);
}
