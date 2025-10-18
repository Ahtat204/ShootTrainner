// Fill out your copyright notice in the Description page of Project Settings.


#include "ShootTrainnerGameState.h"

AShootTrainnerGameState::AShootTrainnerGameState(const FObjectInitializer& ObjectInitializer)
{
}

float FChallenge::EvaluatePerChallengeAccuracy(float distance) const
{
	auto BaseAccuracy = FMath::Exp(-distance / 50);
	
	auto GetDifficultyFactor = [](EDifficultyLevel Difficulty) -> float
	{
		switch (Difficulty)
		{
		case EDifficultyLevel::VeryEasy: return 1.0f;
		case EDifficultyLevel::Easy: return 0.84f;
		case EDifficultyLevel::Normal: return 0.68f;
		case EDifficultyLevel::Hard: return 0.52f;
		case EDifficultyLevel::VeryHard: return 0.52f;
		case EDifficultyLevel::Insane: return 0.25f;
		default: return 1.0f;
		}
	};
	auto FinalAccuracy = BaseAccuracy*GetDifficultyFactor(Difficulty);
	return FMath::Clamp(FinalAccuracy, 0.0f, 1.0f);
}
