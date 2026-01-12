// Fill out your copyright notice in the Description page of Project Settings.


#include "ShootTrainnerPlayerController.h"

#include "UMG/Public/Blueprint/WidgetBlueprintLibrary.h"
#include "Blueprint/UserWidget.h"
#include "Kismet/GameplayStatics.h"


AShootTrainnerPlayerController::AShootTrainnerPlayerController(const FObjectInitializer& ObjectInitializer)
{
	
}

void AShootTrainnerPlayerController::BeginPlay()
{
	Super::BeginPlay();
}

void AShootTrainnerPlayerController::ShowPauseMenu(const bool& switcher)
{
	if (!PauseMenuWidget) UE_LOG(LogTemp, Error, TEXT("Error , Widget  is nullptr"));
	if (MenuWidget==nullptr)
	{
		MenuWidget = CreateWidget<UUserWidget>(this, PauseMenuWidget);
	}
		if (switcher)
		{
			MenuWidget->AddToViewport();
			UGameplayStatics::SetGamePaused(GetWorld(), true);
			UWidgetBlueprintLibrary::SetInputMode_GameAndUIEx(this, MenuWidget,EMouseLockMode::LockOnCapture);
			
		}
		if (!switcher)
		{
			MenuWidget->RemoveFromParent();
			UGameplayStatics::SetGamePaused(GetWorld(), false);
		}
}
