// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "ShootTrainnerPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class SHOOTTRAINNER_API AShootTrainnerPlayerController : public APlayerController
{
	GENERATED_BODY()
protected:
	virtual void BeginPlay() override;

	// Reference to your Widget Blueprint class (set it in the editor)
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "UI")
	TSubclassOf<class UUserWidget> MainWidgetClass;

private:
	// The created widget instance
	UPROPERTY()
	UUserWidget* MainWidget;
};
