// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ShootTrainnerGameState.h"
#include "ShootTrainnerPlayerWidget.h"
#include "GameFramework/Actor.h"
#include "ChallengeGate.generated.h"

#if WITH_EDITOR
	#define LOG(x) UE_LOG(LogTemp, Warning, TEXT("%s"), *FString(x))
#else
	#define LOG(x)
#endif

enum class EDifficultyLevel : uint8;


/**
 *actor acts as the challenge door , when player overlapp with it and press E , he starts challenge
 */
UCLASS(Blueprintable)
class SHOOTTRAINNER_API AChallengeGate : public AActor
{
	GENERATED_BODY()
public:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Component,meta=(AllowPrivateAccess,ToolTip="this Component is the trigger for entering the Challenge"))
	class UBoxComponent* Gate;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Component,meta=(AllowPrivateAccess))
	FChallenge Challenge;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Component,meta=(AllowPrivateAccess))
	UShootTrainnerPlayerWidget* ChallengeWidget;
	// Sets default values for this actor's properties
	AChallengeGate();
	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;
	virtual void NotifyActorEndOverlap(AActor* OtherActor) override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
