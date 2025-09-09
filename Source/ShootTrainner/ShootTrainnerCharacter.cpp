// Copyright Epic Games, Inc. All Rights Reserved.

#include "ShootTrainnerCharacter.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "GameFramework/SpringArmComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "ShootTrainerPlayerState.h"
#include"Components/SceneComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Sound/SoundCue.h"


void AShootTrainnerCharacter::SetCurrentPlayerState(const EPlayerState PlayingState)
{
	if (PlayingState!=this->CurrentPlayinState)
	{
		this->CurrentPlayinState = PlayingState;
	}
}

void AShootTrainnerCharacter::SetCurrentWeaponState(const EWeaponState EWeaponState)
{
	if (CurrentWeaponState != EWeaponState)
	{
		CurrentWeaponState = EWeaponState;
#if UE_EDITOR
		UE_LOG(LogTemp, Warning, TEXT("Weapon state set to: %d"), static_cast<uint8>(CurrentWeaponState));
#endif
	}
}

AShootTrainnerCharacter::AShootTrainnerCharacter(const FObjectInitializer& ObjectInitializer)
{
	WeaponsState = UEnum::GetValueAsString(this->GetCurrentWeaponState());
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);
	SkeletalMeshComponent = GetMesh();
	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = true;
	bUseControllerRotationRoll = false;
	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Character moves in the direction of input...	
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.0f, 0.0f); // ...at this rotation rate
	// Note: For faster iteration times these variables, and many more, can be tweaked in the Character Blueprint
	// instead of recompiling to adjust them
	GetCharacterMovement()->JumpZVelocity = 700.f;
	GetCharacterMovement()->AirControl = 0.35f;
	GetCharacterMovement()->MaxWalkSpeed = 500.f;
	GetCharacterMovement()->MinAnalogWalkSpeed = 20.f;
	GetCharacterMovement()->BrakingDecelerationWalking = 2000.f;
	// Create a camera boom (pulls in towards the player if there is a collision)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(SkeletalMeshComponent,TEXT("head"));
	CameraBoom->TargetArmLength = 400.0f; // The camera follows at this distance behind the character	
	CameraBoom->bUsePawnControlRotation = true; // Rotate the arm based on the controller

	// Create a follow camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	// Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
	FollowCamera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

	GetCharacterMovement()->bOrientRotationToMovement = false;
	//PlayerState=UEnum::GetValueAsString(CurrentWeaponState);

	SetCurrentWeaponState(EWeaponState::Unarmed);
	ReloadSound = CreateDefaultSubobject<USoundCue>("ReloadSound");

	ShootrainerPlayerState=GetPlayerState<AShootTrainerPlayerState>();
	// Note: The skeletal mesh and anim blueprint references on the Mesh component (inherited from Character) 
	// are set in the derived blueprint asset named ThirdPersonCharacter (to avoid direct content references in C++)
}

void AShootTrainnerCharacter::BeginPlay()
{
	// Call the base class  
	Super::BeginPlay();

	CurrentPlayinState=EPlayerState::FreeRoam;
	//Add Input Mapping Context
	if (auto const PlayerController = Cast<APlayerController>(Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<
			UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			//create an if statement for switching IMC between the challenge and the free depending on the  UENUM in the GameSate class 
			Subsystem->AddMappingContext(ChallengeMappingContext, 0);
		}
	}
}

void AShootTrainnerCharacter::PlayChallenge(const FInputActionValue& Value)
{
	const auto bIsPlaying=Value.Get<bool>();
	SetCurrentPlayerState(bIsPlaying?EPlayerState::Challenge:EPlayerState::Challenge);
}


void AShootTrainnerCharacter::PickUpItem(const FInputActionValue& Value)
{
	const auto bisArmed = Value.Get<bool>();
	if (bisArmed)
	{
		AttachPistol(pickUpPistol);
	}
}

void AShootTrainnerCharacter::AttachPistol(AWeapon* Pistol)
{
	if (Pistol)
	{
		//pistol->AttachToComponent(this->SkeletalMeshComponent, FAttachmentTransformRules::KeepRelativeTransform,TEXT("Weapon"));
		Pistol->K2_AttachToComponent(this->SkeletalMeshComponent, TEXT("Weapon"), EAttachmentRule::SnapToTarget,
		                             EAttachmentRule::SnapToTarget, EAttachmentRule::SnapToTarget, true);
		SetCurrentWeaponState(EWeaponState::Armed);
	}
}

void AShootTrainnerCharacter::Shoot(const FInputActionValue& Value)
{
	auto const bActionValue = Value.Get<bool>();
	if (!pickUpPistol) return;
	if (bActionValue && CurrentWeaponState == EWeaponState::Aiming)
	{
		SetCurrentWeaponState(EWeaponState::Firing);

		if (CurrentWeaponState == EWeaponState::Firing)
		{
			UE_LOG(LogTemp, Display, TEXT("Shooting"))
			pickUpPistol->FireBullet();
		}
	}
}


void AShootTrainnerCharacter::Aim(const FInputActionValue& Value)
{
	auto const bIsAiming = Value.Get<bool>();

	if (pickUpPistol)
	{
		SetCurrentWeaponState(bIsAiming ? EWeaponState::Aiming : EWeaponState::Armed);
	}
}

void AShootTrainnerCharacter::Reload(const FInputActionValue& Value)
{
	if (pickUpPistol->CurrentAmmo == 0)
	{
		auto const bIsReloading = Value.Get<bool>();
		if (bIsReloading)
		{
			PlayAnimMontage(ReloadAnimMontage);
			UGameplayStatics::PlaySoundAtLocation(this, ReloadSound, GetActorLocation(), 3,5);
			SetCurrentWeaponState(EWeaponState::Reloading);
			pickUpPistol->ResetAmmo();
		}
		SetCurrentWeaponState(EWeaponState::Aiming);
	}
}

void AShootTrainnerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	// Set up action bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent))
	{
		//Jumping
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Triggered, this, &ACharacter::Jump);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);

		//Moving
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AShootTrainnerCharacter::Move);

		//Looking
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &AShootTrainnerCharacter::Look);

		//interacting
		EnhancedInputComponent->BindAction(Interact, ETriggerEvent::Triggered, this,&AShootTrainnerCharacter::PickUpItem);

#pragma region ChallengeInputs
			//aiming
			EnhancedInputComponent->BindAction(AimAction, ETriggerEvent::Triggered, this, &AShootTrainnerCharacter::Aim);
			EnhancedInputComponent->BindAction(AimAction, ETriggerEvent::Completed, this, &AShootTrainnerCharacter::Aim);
			EnhancedInputComponent->BindAction(FireAction, ETriggerEvent::Started, this, &AShootTrainnerCharacter::Shoot);
			EnhancedInputComponent->BindAction(ReloadAction, ETriggerEvent::Started, this,
											   &AShootTrainnerCharacter::Reload);
#pragma endregion
		
	}
}

void AShootTrainnerCharacter::Move(const FInputActionValue& Value)
{
	// input is a Vector2D
	const FVector2D MovementVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// find out which way is forward
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get forward vector
		const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);

		// get right vector 
		const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

		// add movement 
		AddMovementInput(ForwardDirection, MovementVector.Y);
		AddMovementInput(RightDirection, MovementVector.X);
	}
}

void AShootTrainnerCharacter::Look(const FInputActionValue& Value)
{
	// input is a Vector2D
	const FVector2D LookAxisVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// add yaw and pitch input to controller
		AddControllerYawInput(LookAxisVector.X);
		AddControllerPitchInput(LookAxisVector.Y);
	}
}
