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
	AShootTrainnerPlayerController(const FObjectInitializer& ObjectInitializer); 
	GENERATED_BODY()
protected:
	virtual void BeginPlay() override;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "UI")
	TSubclassOf<UUserWidget> MainWidgetClass;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "UI")
	ACharacter* PlayerCharacter;
private:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "UI", meta=(AllowPrivateAccess=true))
	UShootTrainnerPlayerWidget* MyWidget;
};
