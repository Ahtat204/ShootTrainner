// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InputActionValue.h"
#include "Weapon.h"
#include "ShootTrainnerCharacter.generated.h"

/**
 * Enum class representing the Player State with the Weapon,unarmed is the default Player State , which is 0.
 * 
 */
UENUM(BlueprintType, Category="Weapons")
enum class EWeaponState : uint8
{
	Unarmed UMETA(DisplayName = "Unarmed"),
	Armed UMETA(DisplayName = "Armed"),
	Firing UMETA(DisplayName = "Firing"),
	Loading UMETA(DisplayName = "Loading"),
	Aiming UMETA(DisplayName = "Aiming"),
};

/**
 * Player character class
 */
UCLASS(config=Game)
class AShootTrainnerCharacter : public ACharacter
{
	GENERATED_BODY()
	//despite this is ACharacter-based class , which comes with a SkeletonMeshComponent, this was created to make this character FirstPerson
	USkeletalMeshComponent* SkeletalMeshComponent;
	/** Camera boom positioning the camera behind the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;
	/** Follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* FollowCamera;
	/** MappingContext */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputMappingContext* DefaultMappingContext;
	/** Jump Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* JumpAction;
	/** Move Input Action
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* MoveAction;
	/** Look Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* LookAction;
	/**
	 * pick up input action 
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* Interact;
	/**
	 * Aiming input action
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* AimAction;
	/**
	 * Shooting input action
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* FireAction;
private:
	/** Weapon State on the player*/
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "PlayerState", meta = (AllowPrivateAccess = "true"))
	EWeaponState CurrentWeaponState;
	FString PlayerState;

public:
	//*getter and setter for the weaponState enum
	EWeaponState GetCurrentWeaponState() const { return CurrentWeaponState; };

	void SetCurrentWeaponState(EWeaponState WeaponState);

	/**
	 * the class constructor, set to explicit to prevent accidental conversion
	 * @param ObjectInitializer Internal class to finalize UObject creation (initialize properties) after the real C++ constructor is called.
	 */
	explicit AShootTrainnerCharacter(const FObjectInitializer& ObjectInitializer);

	/**
	 * Weapon to pick up
	 */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = pickup, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<AWeapon> pickUpPistol;

	FString WeaponsState;

	FTransform PistolTransform;

protected:
	/**
	 * Function reponsible for Shooting with weapon
	 * @param Value 
	 */
	void Shoot(const FInputActionValue& Value);
	/**
	 * function used to Aim with the weapon
	 * @param Value 
	 */
	void Aim(const FInputActionValue& Value);
	/** Called for movement input */
	void Move(const FInputActionValue& Value);
	///pick up weapon
	void PickUpItem(const FInputActionValue& Value);
	/** Called for looking input */
	void Look(const FInputActionValue& Value);
	/**
	 * function reponsible for binding different actions , like Moving, Jumping ,Aiming ...
	 * @param PlayerInputComponent 
	 */
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	// To add mapping context
	virtual void BeginPlay() override;

public:
	/**
	 * function used to attach Object to player wanted Socket
	 * @param pistol Actor pistol to pick up
	 */
	void AttachPistol(AWeapon* pistol);
	/** Returns CameraBoom subobject **/
	FORCEINLINE USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	/** Returns FollowCamera subobject **/
	FORCEINLINE UCameraComponent* GetFollowCamera() const { return FollowCamera; }
};


