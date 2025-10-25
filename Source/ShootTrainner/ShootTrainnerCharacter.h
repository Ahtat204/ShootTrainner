// Copyright Epic Games, Inc. All Rights Reserved.
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InputActionValue.h"
#include "InputMappingContext.h"

#include "ShootTrainnerGameState.h"
#include "Weapon.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "ShootTrainnerCharacter.generated.h"


enum class EOverlappingState:uint8;
/**
 * @brief Represents the current weapon-related state of the player.
 *
 * This enum is used to track and manage the player's interaction with weapons. 
 * The default state is Unarmed (value = 0). It can be utilized both in C++ and Blueprints 
 * to control animations, gameplay logic, and weapon handling mechanics.
 *
 * States:
 * - Unarmed   : The player has no weapon equipped (default state).
 * - Armed     : The player has a weapon equipped but is not actively using it.
 * - Firing    : The player is currently firing the equipped weapon.
 * - Reloading : The player is reloading the equipped weapon.
 * - Aiming    : The player is aiming down sights or focusing aim with the weapon.
 */
UENUM(BlueprintType, Category="Weapons", meta=(ToolTip="Represents the current weapon-related state of the player."))
enum class EWeaponState : uint8
{
	Unarmed UMETA(DisplayName = "Unarmed"),
	Armed UMETA(DisplayName = "Armed"),
	Firing UMETA(DisplayName = "Firing"),
	Reloading UMETA(DisplayName = "Reloading"),
	Aiming UMETA(DisplayName = "Aiming"),
};

/**
 * @class AShootTrainnerCharacter
 * @brief Main player character class for the ShootTrainer game.
 *
 * This class extends ACharacter to represent the player in a first-person
 * shooter training environment. It defines camera setup, input bindings,
 * weapon handling, and state management for various gameplay mechanics such as
 * shooting, aiming, reloading, and interacting with the environment.
 *
 * ### Responsibilities:
 * - Provides a first-person camera setup using a spring arm and follow camera.
 * - Handles player input actions (movement, looking, jumping, aiming, shooting, reloading, interacting).
 * - Manages weapon states (Unarmed, Armed, Firing, Reloading, Aiming).
 * - Supports attaching and interacting with weapons (e.g., picking up a pistol).
 * - Integrates animations and sounds for weapon actions (reload montage, reload sound).
 *
 * ### Blueprint Integration:
 * Most properties are exposed to Blueprints to allow designers to modify and
 * extend the character’s behavior without modifying C++ code.
 *
 * @note This class is configured with `config=Game` and designed to be extended in both
 *       C++ and Blueprints.
 */
UCLASS(config=Game)
class AShootTrainnerCharacter : public ACharacter
{
	GENERATED_BODY()

#pragma region Components

	/** Skeletal Mesh for the player (overrides ACharacter's default for first-person view). */
	USkeletalMeshComponent* SkeletalMeshComponent;
	/** Camera boom for positioning the follow camera behind the player. */
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Camera, meta = (AllowPrivateAccess = "true"))
	USpringArmComponent* CameraBoom;
	/** Follow camera providing the player's first-person view. */
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Camera, meta = (AllowPrivateAccess = "true"))
	UCameraComponent* FollowCamera;
#pragma endregion
#pragma region Inputs
	/** Input mapping context used when the player is in a challenge. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputMappingContext* ChallengeMappingContext;
	/** Input mapping context used when the player is free-roaming (not in a challenge). */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputMappingContext* FreeMappingContext;
	/** Input action for jumping. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* JumpAction;
	/** Input action for player movement. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* MoveAction;
	/** Input action for camera look/rotation. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* LookAction;
	/** Input action for interacting with objects (e.g., picking up weapons). */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* Interact;
	/** Input action for aiming with a weapon. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* AimAction;
	/** Input action for firing a weapon. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* FireAction;
	/** Input action for reloading a weapon. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* ReloadAction;
	/**Input Action for entering a challenge */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* PlayAction;
	/**Input Action for Exiting a challenge*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* ExitAction;
	/**	 Input Action fro dropping attached  items, mainly for dropping weapon*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* DropAction;


#pragma endregion
	/** Sound to play when reloading. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Sounds", meta = (AllowPrivateAccess = "true"))
	USoundCue* ReloadSound;
	/** Animation montage to play when reloading. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Input, meta = (AllowPrivateAccess = "true"))
	UAnimMontage* ReloadAnimMontage;
	/** Reference to the underlying APlayerState associated with this character. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "PlayerState", meta = (AllowPrivateAccess = "true"))
	APlayerState* ShootrainerPlayerState;

public:
	/**
	 * Constructor (explicit to prevent accidental implicit conversions).
	 * @param ObjectInitializer Used by Unreal Engine to initialize properties after UObject creation.
	 */
	explicit AShootTrainnerCharacter(const FObjectInitializer& ObjectInitializer);
	/** Weapon currently available for pickup (e.g., a pistol). */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Pickup, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<AWeapon> pickUpPistol;
	/** Internal string representation of the weapon state (debugging). */
	[[maybe_unused]] FString WeaponsState;

protected:
#pragma region InputsFunctions
	/** Handles reloading input. */
	void Reload(const FInputActionValue& Value);
	/** Handles shooting input. */
	void Shoot(const FInputActionValue& Value);
	/** Handles aiming input. */
	void Aim(const FInputActionValue& Value);
	void DropWeapon(const FInputActionValue& Value);
	/** Handles movement input. */
	void Move(const FInputActionValue& Value);
	/** Handles item pickup input. */
	void PickUpItem(const FInputActionValue& Value);
	/** Handles looking input (camera rotation). */
	void Look(const FInputActionValue& Value);
	/** Handles EPlayerState switching and challenge playing*/
	void PlayChallenge(const FInputActionValue& Value);
	/** function responsible for switching between @code  FreeMappingContext @endcode and @code ChallengeMappingContext @endcode */
	void SwitchIMC();
	/** Binds player inputs to character functions. */
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;


#pragma endregion
	/** Called when the game starts or when the player is spawned. */
	virtual void BeginPlay() override;

#pragma region StateMachine
	/**to distinguish if the player is currently playing a challenge or not*/
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "PlayerState", meta = (AllowPrivateAccess = "true"))
	EPlayerState CurrentPlayingState;

public:
	[[nodiscard]] EPlayerState GetCurrentPlayingState() const;

protected:
	/** Current weapon state of the player (e.g., Armed, Firing, Reloading). */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "PlayerState", meta = (AllowPrivateAccess = "true"))
	EWeaponState CurrentWeaponState;
	/** Current overlapping state with actors,it's used mainly for entering challenge*/
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "PlayerState", meta = (AllowPrivateAccess = "true"))
	EOverlappingState PlayerOverlappingState;
#pragma endregion

public:
	/**
	 * Attaches the given pistol to the player’s weapon socket.
	 * @param Pistol The pistol actor to attach.
	 */
	void AttachPistol(AWeapon* Pistol);

	/// 
	UUserWidget* dataWidget;

#pragma region Getters&setters
	/** @return The camera boom subObject. */
	[[nodiscard]] FORCEINLINE USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	/** @return The follow camera subObject. */
	[[nodiscard]] FORCEINLINE UCameraComponent* GetFollowCamera() const { return FollowCamera; }
	void SetCurrentPlayerState(const EPlayerState CurrentPlayerState);
	/** Getter for the current weapon state. */
	[[nodiscard]] FORCEINLINE EWeaponState GetCurrentWeaponState() const { return CurrentWeaponState; }
	/** Setter for the current weapon state. */
	void SetCurrentWeaponState(EWeaponState WeaponState);
	FORCEINLINE [[nodiscard]] EOverlappingState GetOverlappingState() const { return PlayerOverlappingState; };

	void SetOverlappingState(const EOverlappingState OverlappingState){this->PlayerOverlappingState = OverlappingState;};

#pragma endregion
};
