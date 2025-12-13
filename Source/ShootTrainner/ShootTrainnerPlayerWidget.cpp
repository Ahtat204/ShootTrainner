// Fill out your copyright notice in the Description page of Project Settings.


#include "ShootTrainnerPlayerWidget.h"
#include"ShootTrainnerGameState.h"
#include "Components/TextBlock.h"

void UShootTrainnerPlayerWidget::NativeConstruct()
{
	Super::NativeConstruct();
	/*
	if (ChallengeName) ChallengeName->SetText(FText::FromString(Challenge.Name));
	if (ScoreMultiplier) ScoreMultiplier->SetText(FText::AsNumber(Challenge.ScoreMultiplier));
	if (Time) Time->SetText(FText::AsNumber(Challenge.TimeLimit));
	auto difficultyName = UEnum::GetValueAsString(Challenge.Difficulty).Split(TEXT("::"));
	if (Difficulty) Difficulty->SetText(FText::FromString(difficultyName));
	UE_LOG(LogTemp, Log, TEXT(" this function was called "));
	*/
	
	GetWorld()->GetTimerManager().SetTimer(ChallengeTimer,this,&UShootTrainnerPlayerWidget::SetTime,1.0f,true);
	if (ChallengeName)
	{
		ChallengeName->SetText(FText::FromString(Challenge.Name));
	}
	if (ScoreMultiplier)
	{
		ScoreMultiplier->SetText(FText::AsNumber(Challenge.ScoreMultiplier));
	}
	if (Time)
	{
		Time->SetText(FText::AsNumber(Challenge.TimeLimit));
	}
	if (Difficulty)
	{
		Difficulty->SetText(FText::FromString(Challenge.Name));
	}
}

void UShootTrainnerPlayerWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);
}

void UShootTrainnerPlayerWidget::SetChallengeName(UTextBlock* const Challengename)
{
	ChallengeName = Challengename;
}

void UShootTrainnerPlayerWidget::SetTime()
{
	if (Time )
	{
		if (Challenge.TimeLimit<0) return;
		Time->SetText(FText::AsNumber(Challenge.TimeLimit));
		Challenge.TimeLimit--;
	}
	
}

void UShootTrainnerPlayerWidget::SetScoreMultiplier(UTextBlock* const Scoremultiplier)
{
	ScoreMultiplier = Scoremultiplier;
}

void UShootTrainnerPlayerWidget::SetDifficulty(UTextBlock* const difficulty)
{
	Difficulty = difficulty;
}

void UShootTrainnerPlayerWidget::UpdateTime()
{
	if (Challenge.TimeLimit<=0) return; 
	Challenge.TimeLimit--;
#if WITH_EDITOR
	UE_LOG(LogTemp, Log, TEXT("Weapon state set to: %f"),Challenge.TimeLimit);
#endif
	
}
