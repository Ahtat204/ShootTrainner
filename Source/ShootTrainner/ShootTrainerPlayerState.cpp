// Fill out your copyright notice in the Description page of Project Settings.


#include "ShootTrainerPlayerState.h"


void AShootTrainerPlayerState::SetAccuracy(const float accuracy)
{
	this->Accuracy = accuracy;
}
void AShootTrainerPlayerState::SetShotsFiredCount(const uint8 shotsFiredCount)
{
	this->ShotsFiredCount = shotsFiredCount;
}
void AShootTrainerPlayerState::SetTargetHit(const uint8 targetHit)
{
	this->TargetHit = targetHit;
}
void AShootTrainerPlayerState::SetTimePlayed(const float timePlayed)
{
	this->TimePlayed = timePlayed;
}
AShootTrainerPlayerState::AShootTrainerPlayerState(const FObjectInitializer& ObjectInitializer)
{
	Accuracy = 0.0f;
	ShotsFiredCount = 0;
	TargetHit = 0;
}


