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
	Accuracy = 1.0f; // if player hits all center , accuracy should be 100% not O% or making accuracy depends on shots count(this way accuracy will depend on the target ,but accuracy is mathematically calculated , ex:here is propositional to distance  )
	ShotsFiredCount = 0;
	TargetHit = 0;
}

void AShootTrainerPlayerState::BeginPlay()
{
	Super::BeginPlay();
	
}



