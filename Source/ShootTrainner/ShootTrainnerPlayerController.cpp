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

	
	if (GetWorld() && GetWorld()->IsGameWorld())
	{
		PlayerCharacter=GetCharacter();
		if (!MainWidgetClass) UE_LOG(LogTemp, Error, TEXT(" MainWidgetCLass is null"));
		if (auto const shootercharacter=Cast<AShootTrainnerCharacter>(PlayerCharacter))
		{
			if (shootercharacter->GetOverlappingState()==EOverlappingState::Started)
			{
				MyWidget=CreateWidget<UShootTrainnerPlayerWidget>(this, MainWidgetClass);
				if (MyWidget)
				{
					if (auto const ChallengeUI=Cast<UShootTrainnerPlayerWidget>(MyWidget))
					{
						if (AChallengeGate::CurrentChallenge==nullptr)
						{
							UE_LOG(LogTemp, Error, TEXT("%p is null"),static_cast<const void*>(AChallengeGate::CurrentChallenge));
						}
						//	ChallengeUI->Challenge= AChallengeGate::CurrentChallenge->Challenge;
						ChallengeUI->Setup(AChallengeGate::CurrentChallenge->Challenge);
						MyWidget->AddToViewport();
					}
					else
					{
						UE_LOG(LogTemp,Error,TEXT("error in "))
					}
				}
			}
		}
	}

	
}
