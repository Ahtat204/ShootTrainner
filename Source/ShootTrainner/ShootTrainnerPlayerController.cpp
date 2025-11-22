// Fill out your copyright notice in the Description page of Project Settings.


#include "ShootTrainnerPlayerController.h"

#include "ShootTrainnerPlayerWidget.h"
#include "Blueprint/UserWidget.h"

void AShootTrainnerPlayerController::BeginPlay()
{
	Super::BeginPlay();
	
	if (GetWorld() && GetWorld()->IsGameWorld())
	{
		// 1. Get the Widget Class reference
		// Assuming your widget class is loaded via a soft pointer or hardcoded path for testing
        
		
		
		

			// --- Breakpoint 2: Check Class Validity ---
			// Is the Widget Class (asset) successfully found and loaded in PIE?
            
			// 2. Create the Widget
			 MyWidget = CreateWidget<UShootTrainnerPlayerWidget>(this, UShootTrainnerPlayerWidget::StaticClass());

			// --- Breakpoint 3: Check Widget Creation Success ---
			// Is the widget object successfully created (MyWidget is NOT NULL)?
            
			if (MyWidget)
			{
				// 3. Add to Viewport
				MyWidget->AddToViewport();

				// --- Breakpoint 4: Check AddToViewport Execution ---
				// Does the AddToViewport call execute successfully?
                
				// 4. (Optional) Set Input Mode
			
			
		}
	}

	UE_LOG(LogTemp, Warning, TEXT("MyWidget is %s"), MyWidget->IsInViewport() ? TEXT("valid") : TEXT("null"));
}
