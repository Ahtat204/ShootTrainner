// Fill out your copyright notice in the Description page of Project Settings.


#include "ShootTrainnerPlayerController.h"

#include "ChallengeGate.h"
#include "ShootTrainnerPlayerWidget.h"
#include"ShootTrainnerCharacter.h"
#include "Blueprint/UserWidget.h"


AShootTrainnerPlayerController::AShootTrainnerPlayerController(const FObjectInitializer& ObjectInitializer)
{
}

void AShootTrainnerPlayerController::BeginPlay()
{
	Super::BeginPlay();
	/*
	if (!GetWorld() || !GetWorld()->IsGameWorld())
	{
		return;
	}
	PlayerCharacter = GetCharacter();
	if (auto const shootercharacter = Cast<AShootTrainnerCharacter>(PlayerCharacter))
	{
		if (shootercharacter->GetOverlappingState() == EOverlappingState::Started)
		{
			UE_LOG(LogGameMode, Log, TEXT("%d"), shootercharacter->GetOverlappingState());
			if (!MainWidgetClass)
			{
				UE_LOG(LogTemp, Error, TEXT("MainWidget is null "));
				return;
			}
			MyWidget = CreateWidget<UShootTrainnerPlayerWidget>(this, MainWidgetClass);
			if (!MyWidget) return;
			if (auto const ChallengeUI = Cast<UShootTrainnerPlayerWidget>(MyWidget))
			{
				if (GetCurrentChallenge && GetCurrentChallenge.Get())
				{
					//	GetCurrentChallenge = AChallengeGate::CurrentChallenge;
				
				}
			}
		}
	}
	*/
	
}
