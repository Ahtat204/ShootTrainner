// Fill out your copyright notice in the Description page of Project Settings.


#include "ShootTrainnerPlayerController.h"

#include "ShootTrainnerPlayerWidget.h"
#include "Blueprint/UserWidget.h"

void AShootTrainnerPlayerController::BeginPlay()
{
	Super::BeginPlay();
	
	if (GetWorld() && GetWorld()->IsGameWorld())
	{
 MyWidget = CreateWidget<UShootTrainnerPlayerWidget>(this, UShootTrainnerPlayerWidget::StaticClass());
			if (MyWidget)
			{
				
				MyWidget->AddToViewport();			
			
		}
	}

	UE_LOG(LogTemp, Warning, TEXT("MyWidget is %s"), MyWidget->IsInViewport() ? TEXT("valid") : TEXT("null"));
}
