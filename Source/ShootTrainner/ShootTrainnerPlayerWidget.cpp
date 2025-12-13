// Fill out your copyright notice in the Description page of Project Settings.


#include "ShootTrainnerPlayerWidget.h"
#include"ShootTrainnerGameState.h"
#include "Components/TextBlock.h"

void UShootTrainnerPlayerWidget::NativeConstruct()
{
	Super::NativeConstruct();
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
