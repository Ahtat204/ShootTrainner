// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InputActionValue.h"
#include "Weapon.h"
#include "ShootTrainnerCharacter.generated.h"


UENUM(Flags, BlueprintType, Category="Weapons")
enum class EWeaponState : uint8
{
	Unarmed UMETA(DisplayName = "Unarmed"),
	Armed UMETA(DisplayName = "Armed"),
	Firing UMETA(DisplayName = "Firing"),
	Loading UMETA(DisplayName = "Loading"),
	Aiming UMETA(DisplayName = "Aiming"),
};

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
	/** Weapon State on the player*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Weapon, meta = (AllowPrivateAccess = "true"))
	EWeaponState CurrentWeaponState;

	/** Move Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* MoveAction;

	/** Look Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* LookAction;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* Interact;

public:
	//the class constructor 
	AShootTrainnerCharacter();

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = pickup, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<AWeapon> pickUpPistol;

	FTransform PistolTransform;

protected:
	/** Called for movement input */
	void Move(const FInputActionValue& Value);

	/** Called for looking input */
	void Look(const FInputActionValue& Value);

	// APawn interface
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// To add mapping context
	virtual void BeginPlay() override;

public:
	void PickUpItem(const FInputActionValue& Value);
	void AttachPistol(AWeapon* pistol) const;
	/** Returns CameraBoom subobject **/
	FORCEINLINE USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	/** Returns FollowCamera subobject **/
	FORCEINLINE UCameraComponent* GetFollowCamera() const { return FollowCamera; }
};

//Enum class representing the Player-weapon State 
