// Copyright Epic Games, Inc. All Rights Reserved.

#include "ShootTrainnerCharacter.h"
#include "ChallengeGate.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "GameFramework/SpringArmComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "ShootTrainerPlayerState.h"
#include "ShootTrainnerPlayerController.h"
#include"Components/SceneComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Sound/SoundCue.h"
 
void AShootTrainnerCharacter::PlayChallenge(const FInputActionValue& Value)
{
	const auto bIsPlaying = Value.Get<bool>();
	if (PlayerOverlappingState != EOverlappingState::Started) return;
	SetCurrentPlayerState(bIsPlaying ? EPlayerState::Challenge : EPlayerState::FreeRoam);
	SwitchIMC();
	auto EnumString = UEnum::GetValueAsString(CurrentPlayingState);
	LOG("overlapping state is set to Started")
	LOG(EnumString)
}

void AShootTrainnerCharacter::SwitchIMC()
{
	if (auto const PlayerController = Cast<APlayerController>(Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<
			UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			if (CurrentPlayingState == EPlayerState::Challenge)
			{
				Subsystem->RemoveMappingContext(FreeMappingContext);
				Subsystem->AddMappingContext(ChallengeMappingContext, 1);
			}
			if (CurrentPlayingState == EPlayerState::FreeRoam)
			{
				Subsystem->RemoveMappingContext(ChallengeMappingContext);
				Subsystem->AddMappingContext(FreeMappingContext, 0);
			}
		}
	}
}

void AShootTrainnerCharacter::PauseGame(const FInputActionValue& Value)
{
	auto const bIsPaused = Value.Get<bool>();
	if (GetWorld())
	{
		if (const auto PlayerController = Cast<AShootTrainnerPlayerController>(Controller))
		{
			PlayerController->ShowPauseMenu(bIsPaused);
		}
	}
}

void AShootTrainnerCharacter::SetCurrentPlayerState(const EPlayerState PlayingState)
{
	if (PlayingState != this->CurrentPlayingState)
	{
		this->CurrentPlayingState = PlayingState;
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
	PlayerOverlappingState = EOverlappingState::None;
	WeaponsState = UEnum::GetValueAsString(this->GetCurrentWeaponState());
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);
	SkeletalMeshComponent = GetMesh();
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = true;
	bUseControllerRotationRoll = false;
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.0f, 0.0f);
	GetCharacterMovement()->JumpZVelocity = 700.f;
	GetCharacterMovement()->AirControl = 0.35f;
	GetCharacterMovement()->MaxWalkSpeed = 500.f;
	GetCharacterMovement()->MinAnalogWalkSpeed = 20.f;
	GetCharacterMovement()->BrakingDecelerationWalking = 2000.f;
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(SkeletalMeshComponent,TEXT("head"));
	CameraBoom->TargetArmLength = 400.0f; 
	CameraBoom->bUsePawnControlRotation = true; 
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	FollowCamera->bUsePawnControlRotation = false; 
	GetCharacterMovement()->bOrientRotationToMovement = false;
	SetCurrentWeaponState(EWeaponState::Unarmed);
	ReloadSound = CreateDefaultSubobject<USoundCue>("ReloadSound");
	ShootrainerPlayerState = GetPlayerState<AShootTrainerPlayerState>();
}

void AShootTrainnerCharacter::BeginPlay()
{
	Super::BeginPlay();
	CurrentPlayingState = EPlayerState::FreeRoam;
	if (auto const PlayerController = Cast<APlayerController>(Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<
			UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(FreeMappingContext, 0);
		}
	}
}

EPlayerState AShootTrainnerCharacter::GetCurrentPlayingState() const
{
	return CurrentPlayingState;
}

void AShootTrainnerCharacter::PickUpItem(const FInputActionValue& Value)
{
	if (const auto bIsArmed = Value.Get<bool>())
	{
		AttachPistol(pickUpPistol);
	}
}

void AShootTrainnerCharacter::AttachPistol(AWeapon* Pistol)
{
	if (Pistol)
	{
		Pistol->AttachToComponent(this->SkeletalMeshComponent, FAttachmentTransformRules::KeepRelativeTransform,TEXT("Weapon"));
		//Pistol->K2_AttachToComponent(this->SkeletalMeshComponent, TEXT("Weapon"), EAttachmentRule::SnapToTarget,  EAttachmentRule::SnapToTarget, EAttachmentRule::SnapToTarget, true);
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

void AShootTrainnerCharacter::DropWeapon(const FInputActionValue& Value)
{
	if (auto const bIsDroping = Value.Get<bool>())
	{
		if (this->pickUpPistol)
		{
			pickUpPistol->K2_DetachFromActor(EDetachmentRule::KeepWorld, EDetachmentRule::KeepWorld,
			                                 EDetachmentRule::KeepRelative);
		}
	}
}

void AShootTrainnerCharacter::Reload(const FInputActionValue& Value)
{
	if (pickUpPistol->CurrentAmmo == 0)
	{
		if (auto const bIsReloading = Value.Get<bool>())
		{
			PlayAnimMontage(ReloadAnimMontage);
			UGameplayStatics::PlaySoundAtLocation(this, ReloadSound, GetActorLocation(), 3, 5);
			SetCurrentWeaponState(EWeaponState::Reloading);
			pickUpPistol->ResetAmmo();
		}
		SetCurrentWeaponState(EWeaponState::Aiming);
	}
}

void AShootTrainnerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	if (auto EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent))
	{
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Triggered, this, &ACharacter::Jump);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AShootTrainnerCharacter::Move);
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &AShootTrainnerCharacter::Look);
		EnhancedInputComponent->BindAction(Interact, ETriggerEvent::Started, this,  &AShootTrainnerCharacter::PickUpItem);
		EnhancedInputComponent->BindAction(DropAction, ETriggerEvent::Started, this,&AShootTrainnerCharacter::DropWeapon);
		EnhancedInputComponent->BindAction(PlayAction, ETriggerEvent::Started, this,&AShootTrainnerCharacter::PlayChallenge);
		EnhancedInputComponent->BindAction(ExitAction, ETriggerEvent::Completed, this, &AShootTrainnerCharacter::PlayChallenge);
		EnhancedInputComponent->BindAction(PauseAction, ETriggerEvent::Started, this, &AShootTrainnerCharacter::PauseGame);
#pragma region ChallengeInputs
		EnhancedInputComponent->BindAction(AimAction, ETriggerEvent::Triggered, this, &AShootTrainnerCharacter::Aim);
		EnhancedInputComponent->BindAction(AimAction, ETriggerEvent::Completed, this, &AShootTrainnerCharacter::Aim);
		EnhancedInputComponent->BindAction(FireAction, ETriggerEvent::Started, this, &AShootTrainnerCharacter::Shoot);
		EnhancedInputComponent->BindAction(ReloadAction, ETriggerEvent::Started, this,&AShootTrainnerCharacter::Reload);
#pragma endregion
	}
}

void AShootTrainnerCharacter::Move(const FInputActionValue& Value)
{
	const FVector2D MovementVector = Value.Get<FVector2D>();
	if (Controller != nullptr)
	{
		const auto Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);
		const auto ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		const auto RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		AddMovementInput(ForwardDirection, MovementVector.Y);
		AddMovementInput(RightDirection, MovementVector.X);
	}
}

void AShootTrainnerCharacter::Look(const FInputActionValue& Value)
{

	const auto LookAxisVector = Value.Get<FVector2D>();
	if (Controller != nullptr)
	{
		AddControllerYawInput(LookAxisVector.X);
		AddControllerPitchInput(LookAxisVector.Y);
	}
}
