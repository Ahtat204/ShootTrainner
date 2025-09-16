// Fill out your copyright notice in the Description page of Project Settings.


#include "ChallengeGate.h"

#include "ShootTrainnerCharacter.h"
#include "Components/BoxComponent.h"

// Sets default values
AChallengeGate::AChallengeGate()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	Gate=CreateDefaultSubobject<UBoxComponent>(TEXT("Gate"));
	Challenge= FChallenge(EDifficultyLevel::Easy,"",0.0f,0.0f);
}

void AChallengeGate::NotifyActorBeginOverlap(AActor* OtherActor)
{
	Super::NotifyActorBeginOverlap(OtherActor);
	if (auto const character=Cast<AShootTrainnerCharacter>(OtherActor))
	{
		character->SetOverlappingState(EOverlappingState::Started);
	}
}

void AChallengeGate::NotifyActorEndOverlap(AActor* OtherActor)
{
	Super::NotifyActorEndOverlap(OtherActor);
	if (auto const character=Cast<AShootTrainnerCharacter>(OtherActor))
	{
		character->SetOverlappingState(EOverlappingState::Ended);
	}
}

// Called when the game starts or when spawned
void AChallengeGate::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AChallengeGate::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

