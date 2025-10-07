// Fill out your copyright notice in the Description page of Project Settings.


#include "ShootTrainnerPlayerWidget.h"
#include"ShootTrainnerGameState.h"
#include "Components/TextBlock.h"

void UShootTrainnerPlayerWidget::SetChallengeName(UTextBlock* const Challengename)
{
	ChallengeName = Challengename;
}

void UShootTrainnerPlayerWidget::SetTime(UTextBlock* const time)
{
	Time = time;
}

void UShootTrainnerPlayerWidget::SetScoreMultiplier(UTextBlock* const Scoremultiplier)
{
	ScoreMultiplier = Scoremultiplier;
}

void UShootTrainnerPlayerWidget::SetDifficulty(UTextBlock* const difficulty)
{
	Difficulty = difficulty;
}

 void UShootTrainnerPlayerWidget::Setup(const FChallenge& challenge)
{
	this->Challenge = challenge;
	if (ChallengeName) ChallengeName->SetText(FText::FromString(challenge.Name));
	if (ScoreMultiplier) ScoreMultiplier->SetText(FText::AsNumber(challenge.ScoreMultiplier));
	if (Time) Time->SetText(FText::AsNumber(challenge.TimeLimit));
}