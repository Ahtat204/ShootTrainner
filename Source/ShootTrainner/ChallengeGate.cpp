// Fill out your copyright notice in the Description page of Project Settings.


#include "ChallengeGate.h"

#include "ShootTrainnerCharacter.h"
#include "ShootTrainnerPlayerController.h"
#include "ShootTrainnerPlayerWidget.h"
#include "Blueprint/UserWidget.h"
#include "Components/BoxComponent.h"
#include "Components/Widget.h"
AChallengeGate::AChallengeGate()
{
	PrimaryActorTick.bCanEverTick = true;
	Gate = CreateDefaultSubobject<UBoxComponent>(TEXT("Gate"));
	Challenge = FChallenge(EDifficultyLevel::Easy, "", 0.0f, 0.0f, "");
}

void AChallengeGate::NotifyActorBeginOverlap(AActor* OtherActor)
{
	Super::NotifyActorBeginOverlap(OtherActor);
	if (auto const character = Cast<AShootTrainnerCharacter>(OtherActor))
	{
		character->SetOverlappingState(EOverlappingState::Started);
	}
}

void AChallengeGate::NotifyActorEndOverlap(AActor* OtherActor)
{
	Super::NotifyActorEndOverlap(OtherActor);
	if (auto const character = Cast<AShootTrainnerCharacter>(OtherActor))
	{
		character->SetOverlappingState(EOverlappingState::Ended);
	}
}
void AChallengeGate::BeginPlay()
{
	Super::BeginPlay();
}
void AChallengeGate::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
