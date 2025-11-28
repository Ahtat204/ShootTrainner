// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "ShootTrainnerPlayerController.generated.h"

class AShootTrainnerCharacter;
class UShootTrainnerPlayerWidget;
class AChallengeGate;
/**
 * 
 */
UCLASS()
class SHOOTTRAINNER_API AShootTrainnerPlayerController : public APlayerController
{
public:
	AShootTrainnerPlayerController(const FObjectInitializer& ObjectInitializer); ;


	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;

	// Reference to your Widget Blueprint class (set it in the editor)
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "UI")
	TSubclassOf< UUserWidget> MainWidgetClass;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "UI")
	AChallengeGate* GetCurrentChallenge;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "UI")
	ACharacter* PlayerCharacter;

private:
	// The created widget instance
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "UI",meta=(AllowPrivateAccess=true))
	UShootTrainnerPlayerWidget* MyWidget;
};
