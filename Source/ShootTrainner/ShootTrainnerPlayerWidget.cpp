// Fill out your copyright notice in the Description page of Project Settings.


#include "ShootTrainnerPlayerWidget.h"

void UShootTrainnerPlayerWidget::SetChallengeName(UTextBlock* const ChallengeName)
{
	this->ChallengeName = ChallengeName;
}

void UShootTrainnerPlayerWidget::SetTime(UTextBlock* const Time)
{
	this->Time = Time;
}

void UShootTrainnerPlayerWidget::SetScoreMultiplier(UTextBlock* const ScoreMultiplier)
{
	this->ScoreMultiplier = ScoreMultiplier;
}

void UShootTrainnerPlayerWidget::SetDifficulty(UTextBlock* const Difficulty)
{
	this->Difficulty = Difficulty;
}
