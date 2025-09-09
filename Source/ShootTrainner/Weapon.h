// Fill out your copyright notice...

#pragma once

#include "CoreMinimal.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/Actor.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "PhysicsEngine/RadialForceComponent.h"
#include "Sound/SoundWave.h"
#include "Niagara/Public/NiagaraComponent.h"
#include "Weapon.generated.h"

class USoundCue;
class USphereComponent;
class ABullet;

/**
 * @class AWeapon
 * @brief Base class for all weapons in the ShootTrainer game.
 *
 * This class represents a generic weapon (e.g., pistol, rifle, shotgun) and provides
 * the foundation for firing bullets, handling ammunition, and triggering visual/audio effects.
 * It is designed to be extended in Blueprints to customize bullet types, effects, and behavior.
 *
 * ### Responsibilities:
 * - Spawns and fires bullets of the specified class (`BulletClass`).
 * - Manages ammunition (magazine size, current ammo, resetting ammo).
 * - Plays visual (Niagara muzzle flash) and audio (gunshot) effects when firing.
 * - Provides pickup interaction via `PickupSphere`.
 *
 * ### Usage:
 * - Derive a Blueprint class from `AWeapon`.
 * - Assign a `BulletClass` to determine the type of bullet it fires.
 * - Configure mesh, sound, and effects inside the Blueprint.
 */
UCLASS(Blueprintable)
class SHOOTTRAINNER_API AWeapon : public AActor
{
	GENERATED_BODY()

public:
	/** Default constructor. */
	explicit AWeapon(const FObjectInitializer& FObjectInitializer);

	/** Called when the game starts or when spawned. */
	virtual void BeginPlay() override;

	/** Called every frame. */
	virtual void Tick(float DeltaTime) override;

	/**
	 * Fires a bullet from this weapon.
	 * Spawns a bullet actor of type `BulletClass`, plays sound and VFX,
	 * and decreases ammo count.
	 */
	void FireBullet();

	/**
	 * Handles collision detection for this weapon (e.g., pickup logic).
	 * Similar to Unity's OnCollisionEnter.
	 * @param OtherActor The actor this weapon collided with.
	 */
	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;

	/** Resets current ammo back to magazine size (full reload). */
	FORCEINLINE void ResetAmmo() { CurrentAmmo = MagazineSize; }

public:
	/** Skeletal mesh for the weapon (e.g., pistol mesh). */
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Components")
	TObjectPtr<USkeletalMeshComponent> SkeletalMeshComponent;

	/** Class of bullet to spawn when firing (set in Blueprint for flexibility). */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Components", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<ABullet> BulletClass;

	/** Maximum number of bullets this weapon can hold in a magazine. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Ammunition", meta = (ToolTip="",AllowPrivateAccess = "true",ClampMax=100,ClampMin=1))
	uint8 MagazineSize = 20;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Ammunition", meta = (AllowPrivateAccess = "true",ClampMin=1))
	/** Current amount of ammunition remaining in the magazine. */
	uint8 CurrentAmmo = MagazineSize;

	/** Collision sphere used for pickup interaction. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Components", meta = (AllowPrivateAccess = "true"))
	USphereComponent* PickupSphere;

	/** Gunshot sound effect played when firing. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Sounds", meta = (AllowPrivateAccess = "true"))
	USoundCue* FireSound;

	/** Active bullet instances fired by this weapon. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Components", meta = (AllowPrivateAccess = "true"))
	TArray<ABullet*> Bullets;

	/** Niagara component for visual gunfire effect (e.g., muzzle flash). */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Components")
	UNiagaraComponent* NiagraComponent;
};


/**
 * @class ABullet
 * @brief Represents a bullet fired by a weapon.
 *
 * A bullet is a simple projectile actor that uses Unreal’s
 * `UProjectileMovementComponent` to simulate flight and physics.
 *
 * ### Responsibilities:
 * - Provides mesh and collision representation of a bullet.
 * - Moves through the world using projectile physics.
 * - Detects collisions via its capsule component.
 *
 * ### Usage:
 * - Create Blueprint-derived bullet classes for different behavior
 *   (explosive bullets, tracers, etc.).
 * - Assign the Blueprint class to `AWeapon::BulletClass` to use it.
 */
UCLASS(Blueprintable)
class ABullet : public AActor
{
	GENERATED_BODY()

public:
	/** Default constructor. */
	explicit ABullet(const FObjectInitializer& FObjectInitializer);

	/** @return The projectile movement component (controls flight physics). */
 [[nodiscard]]	UProjectileMovementComponent* GetProjectileMovementComponent() const { return ProjectileMovementComponent; }

private:
	/** Static mesh representing the bullet's visual appearance. */
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Components", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UStaticMeshComponent> StaticMeshComponent;

	/** Component responsible for projectile movement (speed, gravity, trajectory). */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Components", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UProjectileMovementComponent> ProjectileMovementComponent;

	/** Capsule collider for hit detection and overlaps. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Components", meta = (AllowPrivateAccess = "true"))
	UCapsuleComponent* CapsuleComponent;

	/* Alternative collision option (currently unused). */
	// UBoxComponent* BoxComponent;
};
