// Fill out your copyright notice in the Description page of Project Settings.


#include "ShootTrainnerPlayerController.h"

#include "Blueprint/UserWidget.h"

void AShootTrainnerPlayerController::BeginPlay()
{
	Super::BeginPlay();
	if (MainWidgetClass)
	{
		// Create the widget and assign this controller as the owning player
		MainWidget = CreateWidget<UUserWidget>(this, MainWidgetClass);
		if (MainWidget)
		{
			MainWidget->AddToViewport();
		}
	}
	UE_LOG(LogTemp, Warning, TEXT("PlayerController BeginPlay world: %s"), *GetWorld()->GetName());
	UE_LOG(LogTemp, Warning, TEXT("MainWidgetClass is %s"), MainWidgetClass ? TEXT("valid") : TEXT("null"));
}
