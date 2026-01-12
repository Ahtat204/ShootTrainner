// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "ShootTrainnerPlayerController.generated.h"

class AShootTrainnerCharacter;

/**
 * 
 */
UCLASS()
class SHOOTTRAINNER_API AShootTrainnerPlayerController : public APlayerController
{
public:
	AShootTrainnerPlayerController(const FObjectInitializer& ObjectInitializer); 
	GENERATED_BODY()
	virtual void BeginPlay() override;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "UI")
	TSubclassOf<UUserWidget> PauseMenuWidget;
	UUserWidget* MenuWidget;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "UI")
	ACharacter* PlayerCharacter;
	UFUNCTION(BlueprintCallable, Category = "UI")
	void ShowPauseMenu(const bool& switcher);
};
